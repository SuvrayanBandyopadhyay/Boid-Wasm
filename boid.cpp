#include<iostream>
#include<vector>
#include<time.h>
#include<emscripten.h>

std::vector<float> x;
std::vector<float> y;
std::vector<float> v;
std::vector<float> dx;
std::vector<float> dy;

float cx = 0.0f;
float cy = 0.0f; //Center of mass

float mdx = 0.0f;
float mdy = 0.0f; //Mean of directions


extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void addBoid()
    {
        x.push_back((((float)rand()/(float)RAND_MAX)-0.5f)*2.0f);
        y.push_back((((float)rand()/(float)RAND_MAX)-0.5f)*2.0f);
        v.push_back(0.01f + ((float)rand()/(float)RAND_MAX)*0.02f);
        float dirx = (((float)rand()/(float)RAND_MAX)-0.5f)*2.0f;
        float diry = (((float)rand()/(float)RAND_MAX)-0.5f)*2.0f;
        float len = fmax(sqrtf(dirx*dirx + diry*diry),0.00001f);
        dirx /= len;
        diry /= len;
        dx.push_back(dirx);
        dy.push_back(diry);
    }

    EMSCRIPTEN_KEEPALIVE
    void init(int n)
    {
        srand(time(NULL));
        for(int i=0;i<n;i++)
        {
            addBoid();
        }
    }

    EMSCRIPTEN_KEEPALIVE
    float dist(float x1,float y1,float x2,float y2)
    {
        return sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    }

    EMSCRIPTEN_KEEPALIVE
    void computeCenter()
    {
        cx = 0.0f;
        cy = 0.0f;
        for(size_t i = 0; i < x.size(); i++)
        {
            cx += x[i];
            cy += y[i];
        }
        cx /= (float)x.size();
        cy /= (float)y.size();
    }

    void computeDirection()
    {
        mdx = 0.0f;
        mdy = 0.0f;
        for(size_t i = 0; i < dx.size(); i++)
        {
            mdx += dx[i];
            mdy += dy[i];
        }
        mdx /= (float)dx.size();
        mdy /= (float)dy.size();
    }

    EMSCRIPTEN_KEEPALIVE
    void rule1(int id)
    {
        float pcx = (cx*x.size() - x[id])/fmax(1.0f, (float)(x.size() - 1));
        float pcy = (cy*y.size() - y[id])/fmax(1.0f, (float)(y.size() - 1)); 
        dx[id] += (pcx - x[id]) * 0.02f; //Move it 1% towards percieved center
        dy[id] += (pcy - y[id]) * 0.02f;
    }

    EMSCRIPTEN_KEEPALIVE
    void rule2(int id)
    {
        float sep = 0.25f;
        for(int i=0;i<x.size();i++)
        {
            if(i==id)
            {
                continue;
            }

            if(dist(x[id],y[id],x[i],y[i])<0.11)
            {
                dx[id] -= (x[i]-x[id])*sep;
                dy[id] -= (y[i]-y[id])*sep;   
            }
        }
    }

    EMSCRIPTEN_KEEPALIVE
    void rule3(int id)
    {
        float pdx = (mdx*x.size() - dx[id])/fmax(1.0f, (float)(dx.size() - 1));
        float pdy = (mdy*y.size() - dy[id])/fmax(1.0f, (float)(y.size() - 1)); 
        dx[id] += (pdx - dx[id]) * 0.01f; //Move it 1% towards percieved direction
        dy[id] += (pdy - dy[id]) * 0.01f;
    }

    EMSCRIPTEN_KEEPALIVE
    void run()
    {
        computeCenter();
        computeDirection();

        for(int i=0;i<x.size();i++)
        {
            rule1(i);
            rule2(i);
            rule3(i);
            
            float dirx = dx[i];
            float diry = dy[i];

            float len = fmax(sqrtf(dirx*dirx + diry*diry),0.00001f);
            dirx /= len;
            diry /= len;

            dx[i] = dirx;
            dy[i] = diry;
            
            float sconst = 0.2f;

            x[i] = x[i] + dx[i]*v[i]*sconst;
            y[i] = y[i] + dy[i]*v[i]*sconst;
            if(x[i]>1.0f) x[i]=-1.0f;
            if(x[i]<-1.0f) x[i]=1.0f;   
            if(y[i]>1.0f) y[i]=-1.0f;
            if(y[i]<-1.0f) y[i]=1.0f;
            
        }
    }

    //Get x values
    float* getXPtr()
    {
        return x.data();
    }

    int getSize()
    {
        return x.size();
    }

    float* getYPtr()
    {
        return y.data();
    }
}