#pragma once
#include <SFML/Graphics.hpp>
#include "Bezier.hpp"
#include "Math.hpp"
#include "global.hpp"
#include "Bitmap.hpp"
#include "PhongReflectionProcessor.hpp"
#include "PolygonInterior.hpp"

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

    void initializeStructures()
    {
        triangleXs = triangleYs = vector<int>();
        bottomTriangles = topTriangles = vector<Triangle>();
        topTrianglesPoints = bottomTrianglesPoints = vector<vector<Point>>(meshSize);
        topTrianglesPoints = vector<vector<Point>>(meshSize);
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

        for (float x : triangleXs)
        {
            for (float y : triangleYs)
            {
                allPoints.push_back({x, y});

                allVertices.push_back({x, y});
                allVertices.push_back({x + disX, y});
                allVertices.push_back({x + disX, y + disY});

                bottomTriangles.push_back(Triangle({x, y}, {x + disX, y}, {x + disX, y + disY}));
            }
        }

        for (float x : triangleXs)
        {
            for (float y : triangleYs)
            {
                allVertices.push_back({x, y});
                allVertices.push_back({x, y + disY});
                allVertices.push_back({x + disX, y + disY});

                topTriangles.push_back(Triangle({x, y}, {x, y + disY}, {x + disX, y + disY}));
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

    void processFrame(bool bezierChanged, bool meshChanged, int _meshDensityX = -1, int _meshDensityY = -1)
    {
        if (meshChanged)
            initializeMeshStructure(_meshDensityX, _meshDensityY);

        if (bezierChanged || meshChanged)
        {
            calculateHeights();
            calculateNormalVectors();
        }
        calculateColors();
    }

    void calculateNormalVectors()
    {
        for (Point point : allPoints)
        {
            int x = point.x;
            int y = point.y;
            bitmap.N[x][y] = cross(bezier.tangentX(bitmap.xPoints[x], bitmap.yPoints[y]),
                                   bezier.tangentY(bitmap.xPoints[x], bitmap.yPoints[y]))
                                 .normalized();
        }

        // for (Triangle t : topTriangles)
        // {
        //     vector<Point> points = PolygonInterior::getInteriorPoints({t.a, t.b, t.c});

        //     vector<Vertex> pixels;
        //     for(Point p: points)
        //     {
        //         // cout << "halo " << p.x << " "<< p.y << endl;
        //         pixels.push_back(Vector2f(p.x, H - p.y));
        //     }

        //     for (auto &v : pixels)
        //         v.color = Color::Yellow;

        //     cout << pixels.size() << endl;
        //     window.draw(&pixels[0], pixels.size(), sf::Points);
        // }

        for (vector<Point> vp : bottomTrianglesPoints)
        {
            for (Point p : vp)
            {
                int x = p.x;
                int y = p.y;
                bitmap.N[x][y] = cross(bezier.tangentX(bitmap.xPoints[x], bitmap.yPoints[y]),
                                       bezier.tangentY(bitmap.xPoints[x], bitmap.yPoints[y]))
                                     .normalized();
            }
        }

        for (vector<Point> vp : topTrianglesPoints)
        {
            for (Point p : vp)
            {
                int x = p.x;
                int y = p.y;
                bitmap.N[x][y] = cross(bezier.tangentX(bitmap.xPoints[x], bitmap.yPoints[y]),
                                       bezier.tangentY(bitmap.xPoints[x], bitmap.yPoints[y]))
                                     .normalized();
            }
        }
    }

    void calculateHeights()
    {
        for (Point point : allPoints)
        {
            int x = point.x;
            int y = point.y;
            bitmap.height[x][y] = bezier.z(bitmap.xPoints[x], bitmap.yPoints[y]);
        }

        for (vector<Point> vp : bottomTrianglesPoints)
        {
            for (Point p : vp)
            {
                int x = p.x;
                int y = p.y;
                bitmap.height[x][y] = bezier.z(bitmap.xPoints[x], bitmap.yPoints[y]);
            }
        }
        
        for (vector<Point> vp : topTrianglesPoints)
        {
            for (Point p : vp)
            {
                int x = p.x;
                int y = p.y;
                bitmap.height[x][y] = bezier.z(bitmap.xPoints[x], bitmap.yPoints[y]);
            }
        }
    }

    void calculateColors()
    {
        // for (int y = 0; y < H; y++)
        //     for (int x = 0; x < W; x++)
        //     {
        //         bitmap.color[x][y] = prp.computePixelColor(x, y);
        //         // cout << "color w (x, y) " << x << " " << y << " " << bitmap.color[x][y].toInteger() << endl;
        //     }

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
    void gpu()
    {
        int cnt = meshDensityX * meshDensityY;
        VertexArray gpuBottomTriangles(sf::Triangles, cnt * 3);
        VertexArray gpuTopTriangles(sf::Triangles, cnt * 3);

        int index = 0;
        for (float x : triangleXs)
        {
            for (float y : triangleYs)
            {
                allPoints.push_back({x, y});

                allVertices.push_back({x, y});
                allVertices.push_back({x + disX, y});
                allVertices.push_back({x + disX, y + disY});

                bottomTriangles.push_back(Triangle({x, y}, {x + disX, y}, {x + disX, y + disY}));

                gpuBottomTriangles[index].color = Color::Red;
                gpuBottomTriangles[index++].position = {x, H - y};

                gpuBottomTriangles[index].color = Color::Green;
                gpuBottomTriangles[index++].position = {x + disX, H - y};

                gpuBottomTriangles[index].color = Color::Blue;
                gpuBottomTriangles[index++].position = {x + disX, H - (y + disY)};
            }
        }

        index = 0;
        for (float x : triangleXs)
        {
            for (float y : triangleYs)
            {
                allVertices.push_back({x, y});
                allVertices.push_back({x, y + disY});
                allVertices.push_back({x + disX, y + disY});
                topTriangles.push_back(Triangle({x, y}, {x, y + disY}, {x + disX, y + disY}));

                gpuTopTriangles[index].color = Color::Cyan;
                gpuTopTriangles[index++].position = {x, H - y};

                gpuTopTriangles[index].color = Color::Yellow;
                gpuTopTriangles[index++].position = {x, H - (y + disY)};

                gpuTopTriangles[index].color = Color::Magenta;
                gpuTopTriangles[index++].position = {x + disX, H - (y + disY)};
            }
        }
    }
};