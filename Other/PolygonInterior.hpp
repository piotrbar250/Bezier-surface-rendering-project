#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Bitmap.hpp"
#include "global.hpp"
#include <cmath>

using namespace std;
using namespace sf;

struct Point
{
    float x, y;
    Point() {}
    Point(float x, float y) : x(x), y(y) {}

    bool operator==(const Point &p)
    {
        return x == p.x && y == p.y;
    }
    
    friend float area(const Point& a, const Point& b, const Point& c)
    {   
        float det = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        return fabs(det) / 2.0f;
    }
};

struct Segment
{
    Point a, b;
    float ymax, x;
    float mInv;
    bool up;
    Segment() {}
    Segment(Point a, Point b) : a(a), b(b) {}
    Segment(Point a, Point b, float ymax, float x, float mInv, bool up) : a(a), b(b), ymax(ymax), x(x), mInv(mInv), up(up) {}

    bool operator==(const Segment &s)
    {
        return a == s.a && b == s.b;
    }
    bool isVertical() const
    {
        return a.x == b.x;
    }
};


std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "Point(" << p.x << ", " << p.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Segment& s) {
    os << "Segment["
       << "a: " << s.a << ", "
       << "b: " << s.b << ", "
       << "ymax: " << s.ymax << ", "
       << "x: " << s.x << ", "
       << "mInv: " << s.mInv << "]";
    return os;
}

struct Node
{
    Segment s;
    Node *next;

    Node() : next(nullptr) {}
    Node(Segment s) : s(s), next(nullptr) {}

    static void insert(Node *&head, Segment &s)
    {
        Node **ptr = &head;

        while (*ptr)
        {
            if (s.x < (*ptr)->s.x || s.x + s.mInv < (*ptr)->s.x + (*ptr)->s.mInv)
                break;
            else
                ptr = &((*ptr)->next);
        }

        Node *newNode = new Node(s);
        newNode->next = (*ptr);
        *ptr = newNode;
    }

    static bool remove(Node *&head, int ymin)
    {
        Node **ptr = &head;
        while (*ptr)
        {
            if (ymin == (*ptr)->s.ymax)
                break;
            else
                ptr = &((*ptr)->next);
        }

        if (!*ptr)
            return false;

        Node *toDelete = *ptr;
        *ptr = (*ptr)->next;
        delete toDelete;
        return true;
    }

    static void apply(Node *head, function<void(Segment &s)> func)
    {
        Node *current = head;
        while (current)
        {
            func(current->s);
            current = current->next;
        }
    }
};

class PolygonInterior
{
public:
    static vector<Point> getInteriorPoints(vector<Point> vertexes) // vertexes describe the Polygon, we assume it doesnt have any self-intersections
    {

        vector<Vertex> pixels;
        vector<Point> points;

        vector<Segment> buckets[H];
        int buckets_y_min = H;
        int buckets_total_size = vertexes.size();

        for (int i = 0; i < H; i++)
            buckets[i] = vector<Segment>();

        vector<Segment> segments = vector<Segment>();
        for (int i = 1; i < vertexes.size(); i++)
            segments.push_back(Segment({vertexes[i - 1].x, vertexes[i - 1].y}, {vertexes[i].x, vertexes[i].y}));

        segments.push_back(Segment({vertexes.back().x, vertexes.back().y}, {vertexes.front().x, vertexes.front().y}));


        for (Segment &s : segments)
        {
            float x_t, y_t;
            float x_b, y_b;

            if (s.a.y <= s.b.y)
            {
                x_t = s.b.x;
                y_t = s.b.y;

                x_b = s.a.x;
                y_b = s.a.y;

                if (s.a.x <= s.b.x)
                    s.up = true;
                else
                    s.up = false;
            }
            else
            {
                x_t = s.a.x;
                y_t = s.a.y;

                x_b = s.b.x;
                y_b = s.b.y;

                if (s.a.x <= s.b.x)
                    s.up = false;
                else
                    s.up = true;
            }

            s.ymax = y_t;
            s.x = x_b;
            if (y_t == y_b)
                s.mInv = 0;
            else
                s.mInv = float(x_t - x_b) / float(y_t - y_b);

            // cout << s << endl << endl;

            // Bucket sort
            buckets[int(y_b)].push_back(s);
            buckets_y_min = min(buckets_y_min, int(y_b));
        }

        // AET list
        Node *head = nullptr;

        // for(int i = 0; i < H; i++)
        // {
        //     if(buckets[i].size() > 0)
        //     {
        //         // cout << "bucket nr " << i << " ";
        //         for(Segment s: buckets[i])
        //             // cout << s << endl;
                
        //         // cout << endl << endl << endl;
        //     }
        // }

        while (buckets_total_size > 0 || head)
        {
            // cout << "zaczynam wstawiac" << endl;
            for (auto &s : buckets[buckets_y_min])
            {
                // cout << "wstawiam s do bucketa " << s << endl << endl;
                Node::insert(head, s);

            }
            // cout << "skonczylem wstawiac" << endl << endl;
            buckets_total_size -= buckets[buckets_y_min].size();
            buckets[buckets_y_min].clear();

            Node *current = head;
            if (current)
            {
                // cout << "current: " << current->s << endl << endl;
                Segment s_current(current->s);
                pixels.push_back(Vector2f(s_current.x, H - buckets_y_min));
                points.push_back({s_current.x, float(buckets_y_min)});
                if(!current->next)
                {
                    // cout << "petla sie nie odpali dla y " << buckets_y_min << endl << endl;
                }
                // cout << "zaczynam " << endl;
                while (current->next)
                {
                    // cout << "current_next: " << current->next->s << endl << endl;
                    Segment s_next(current->next->s);
                    // cout << "rysuje miedzy pikslami " << s_current.x +1 << " " << s_next.x << " na y " << buckets_y_min << endl << endl;
                    for (int x = s_current.x+1; x <= s_next.x; x++)
                    {
                        pixels.push_back(Vector2f(x, H - buckets_y_min));
                        points.push_back({float(x), float(buckets_y_min)});
                    }

                    s_current = s_next;
                    current = current->next;
                }

            }
           

            while (Node::remove(head, buckets_y_min))
                ;

            buckets_y_min++;

            auto updateX = [&pixels](Segment &s)
            {
                // if(s.up)
                //     s.x += s.mInv;
                // else
                //     s.x -= s.mInv;

                s.x += s.mInv;
            };

            Node::apply(head, updateX);
        }
        // return pixels;
        return points;
    }

    static void drawPolygon()
    {
        vector<Point> polygon = {
            {100,100}, {200, 50}, {300, 120}, {500, 500}, {300, 300}, {150, 250}, {200, 120}
        };

        // vector<Point> polygon = {
        //     {50, 20}, {300, 500}
        // };

        //:((()))
        // vector<Point> polygon = {
        //     {100, 100}, {150, 300}, {120, 400}
        // };

        // vector<Point> polygon = {
        //     {100, 100}, {400, 100}, {100, 400}
        // };

        // vector<Point> polygon = {
        //     {300, 100}, {100, 100}, {100, 300}
        // };

        // vector<Point> polygon = {
        //     {300, 100}, {100, 100}, {300, 300}
        // };

        // vector<Point> polygon = {
        //     {100, 100}, {300, 300}, {100, 300}};

        // vector<Point> polygon = {
        //     {400, 100}, {200, 500}, {600, 700}
        // };
        // vector<Point> polygon = {
        //     {100, 100}, {300, 100}, {300, 300}, {100, 300}
        // };


        // vector<Vertex> pixels = getInteriorPoints(polygon);

        // for (auto &v : pixels)
        //     v.color = Color::Yellow;

        // window.draw(&pixels[0], pixels.size(), sf::Points);
    }
};

/*
    info for chat gpt

    this triangle is being drawn correctly
    vector<Point> polygon = {
            {100, 100}, {300, 100}, {300, 300}
        };

    now this is also correct:
    // vector<Point> polygon = {
        //     {100, 100}, {300, 300}, {100, 300}
        // };

    but this doesnt work:
        vector<Point> polygon = {
            {100, 100}, {300, 300}, {100, 300}
        }; - it draws only segment from {100, 100} to {300, 300} and from {300, 300} to {100, 300} there is no filling and no segment from {100, 300} to {100, 100}
*/