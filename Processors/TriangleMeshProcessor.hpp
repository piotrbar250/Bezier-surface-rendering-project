#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"
#include "PhongReflectionProcessor.hpp"
#include "PolygonInterior.hpp"
#include "NormalmapProcessor.hpp"

class TriangleMeshProcessor
{
public:
    struct Triangle
    {
        Point a, b, c;
        Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {}
    };

    Bezier &bezier;
    PhongReflectionProcessor &prp;

    int meshDensityX, meshDensityY, meshSize;
    int disX, disY;

    vector<int> triangleXs, triangleYs;

    vector<Triangle> bottomTriangles, topTriangles;
    vector<vector<Point>> bottomTrianglesPoints, topTrianglesPoints;
    vector<Point> allVertices;
    vector<Point> allPoints;

    TriangleMeshProcessor(Bezier &bezier, PhongReflectionProcessor &prp) : bezier(bezier), prp(prp) {}

    void processFrame(bool bezierChanged, bool meshChanged, int _meshDensityX = -1, int _meshDensityY = -1, bool launchNormalmap = false, bool shutdownNormalmap = false)
    {
        if (meshChanged)
            initializeMeshStructure(_meshDensityX, _meshDensityY);

        if (bezierChanged || meshChanged)
        {
            computeSurface();
        }
        
        if(launchNormalmap)
            NormalmapProcessor::apply();
        
        if(shutdownNormalmap)
            computeSurface();

        computeColors();
    }

    void initializeStructures()
    {
        triangleXs = triangleYs = vector<int>();
        bottomTriangles = topTriangles = vector<Triangle>();
        topTrianglesPoints = bottomTrianglesPoints = vector<vector<Point>>(meshSize/2);
        allVertices = vector<Point>();
        allPoints = vector<Point>();
    }

    void initializeMeshStructure(int _meshDensityX, int _meshDensityY)
    {
        meshDensityX = _meshDensityX;
        meshDensityY = _meshDensityY;
        meshSize = 2 * meshDensityX * meshDensityY;

        initializeStructures();

        triangleXs.push_back(0);
        disX = W / meshDensityX;
        for (int i = 1; i < meshDensityX; i++)
            triangleXs.push_back(triangleXs.back() + disX);

        triangleYs.push_back(0);
        disY = H / meshDensityY;
        for (int i = 1; i < meshDensityY; i++)
            triangleYs.push_back(triangleYs.back() + disY);
        
        int modDisX = disX-1;
        int modDisY = disY-1;

        int lastX = triangleXs.back();
        int lastY = triangleYs.back();

        for (float x : triangleXs)
        {
            for (float y : triangleYs)
            {
                allPoints.push_back({x, y});

                allVertices.push_back({x, y});
                allVertices.push_back({x + modDisX, y});
                allVertices.push_back({x + modDisX, y + modDisY});

                bottomTriangles.push_back(Triangle({x, y}, {x + modDisX, y}, {x + modDisX, y + modDisY}));
            }
        }

        for (float x : triangleXs)
        {
            for (float y : triangleYs)
            {
                allVertices.push_back({x, y});
                allVertices.push_back({x, y + modDisY});
                allVertices.push_back({x + modDisX, y + modDisY});

                topTriangles.push_back(Triangle({x, y}, {x, y + modDisY}, {x + modDisX, y + modDisY}));
            }
        }

        int index = 0;
        for (Triangle t : bottomTriangles)
        {
            bottomTrianglesPoints[index++] = PolygonInterior::getInteriorPoints({t.a, t.b, t.c});
        }

        index = 0;
        for (Triangle t : topTriangles)
        {
            topTrianglesPoints[index++] = PolygonInterior::getInteriorPoints({t.a, t.b, t.c});
        }
    }

    void computeSurface()
    {
        int x, y;
        for(Triangle t: topTriangles)
        {
            float tx[] = {t.a.x, t.b.x, t.c.x};
            float ty[] = {t.b.y, t.b.y, t.c.y};

            for(int i = 0; i < 3; i++) 
            {
                x = tx[i];
                y = ty[i];
                bitmap.N[x][y] = cross(bezier.tangentX(bitmap.xPoints[x], bitmap.yPoints[y]),
                                    bezier.tangentY(bitmap.xPoints[x], bitmap.yPoints[y]))
                                    .normalized();

                bitmap.height[x][y] = bezier.z(bitmap.xPoints[x], bitmap.yPoints[y]);
            }
        }

        for(Triangle t: bottomTriangles)
        {
            float tx[] = {t.a.x, t.b.x, t.c.x};
            float ty[] = {t.b.y, t.b.y, t.c.y};

            for(int i = 0; i < 3; i++) 
            {
                x = tx[i];
                y = ty[i];
                bitmap.N[x][y] = cross(bezier.tangentX(bitmap.xPoints[x], bitmap.yPoints[y]),
                                    bezier.tangentY(bitmap.xPoints[x], bitmap.yPoints[y]))
                                    .normalized();
                bitmap.height[x][y] = bezier.z(bitmap.xPoints[x], bitmap.yPoints[y]);
            }
        }
    
        int index = 0;
        for (vector<Point> vp : topTrianglesPoints)
        {
            Triangle t = topTriangles[index];
            float abcArea = area(t.a, t.b, t.c);
            
            for (Point p : vp)
            {
                float abpArea = area(t.a, t.b, p);
                float acpArea = area(t.a, t.c, p);
                float bcpArea = area(t.b, t.c, p);

                float alfa =  bcpArea / abcArea;
                float beta = acpArea / abcArea;
                float gamma = abpArea / abcArea;
                
                int x = p.x;
                int y = p.y;
               
                bitmap.N[x][y] = bitmap.N[int(t.a.x)][int(t.a.y)] * alfa + bitmap.N[int(t.b.x)][int(t.b.y)] * beta + bitmap.N[int(t.c.x)][int(t.c.y)] * gamma;
                bitmap.height[x][y] = bitmap.height[int(t.a.x)][int(t.a.y)] * alfa + bitmap.height[int(t.b.x)][int(t.b.y)] * beta + bitmap.height[int(t.c.x)][int(t.c.y)] * gamma;
            }
            index++;
        }

        index = 0;        
        for (vector<Point> vp : bottomTrianglesPoints)
        {
            Triangle t = bottomTriangles[index];
            float abcArea = area(t.a, t.b, t.c);
            for (Point p : vp)
            {
                float abpArea = area(t.a, t.b, p);
                float acpArea = area(t.a, t.c, p);
                float bcpArea = area(t.b, t.c, p);

                float alfa =  bcpArea / abcArea;
                float beta = acpArea / abcArea;
                float gamma = abpArea / abcArea;
                

                int x = p.x;
                int y = p.y;
                bitmap.N[x][y] = bitmap.N[int(t.a.x)][int(t.a.y)] * alfa + bitmap.N[int(t.b.x)][int(t.b.y)] * beta + bitmap.N[int(t.c.x)][int(t.c.y)] * gamma;
                bitmap.height[x][y] = bitmap.height[int(t.a.x)][int(t.a.y)] * alfa + bitmap.height[int(t.b.x)][int(t.b.y)] * beta + bitmap.height[int(t.c.x)][int(t.c.y)] * gamma;
            }
            index++;
        }
    }

    void computeColors()
    {
        for (vector<Point> vp : bottomTrianglesPoints)
        {
            for (Point p : vp)
            {
                int x = p.x;
                int y = p.y;
                bitmap.color[x][y] = prp.computePixelColor(x, y);
            }
        }

        for (vector<Point> vp : topTrianglesPoints)
        {
            for (Point p : vp)
            {
                int x = p.x;
                int y = p.y;
                bitmap.color[x][y] = prp.computePixelColor(x, y);
            }
        }

    }
};