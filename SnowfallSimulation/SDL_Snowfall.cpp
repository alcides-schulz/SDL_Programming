#include "../SDL_Framework.h"

class Snowflake {
private:
    Vector2D mPosition;
    Vector2D mVelocity;
    Vector2D mAcceleration;
    int mRadius;
    float mAngle;
    int mDirection;
    int mOffset;
public:
    Snowflake(int x, int y)
    {
        mPosition = Vector2D(x, y);
        mVelocity = Vector2D(0, 0);
        mAcceleration = Vector2D(0, 0);
        mRadius = rand() % 8 + 1;
        mAngle = (float)(rand() % 6);
        mDirection = rand() % 2 ? 1 : -1;
        mOffset = 0;
    }

    void ApplyForce(Vector2D force)
    {
        Vector2D adjusted_force = Vector2D(force.x, force.y);
        adjusted_force.Multiply((float)mRadius);
        mAcceleration.Add(adjusted_force);
    }

    void UpdatePosition()
    {
        mOffset = (int)(sin(mAngle * 2) * 2 * mRadius);
        mVelocity.Add(mAcceleration);
        if (mVelocity.y > (double)(mRadius * 0.2)) {
            mVelocity.y = (float)(mRadius * 0.2);
        }
        mPosition.Add(mVelocity);
        mAcceleration.Multiply(0);
        mAngle += mDirection * (mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y) / 200;
    }

    Vector2D GetPosition()
    {
        Vector2D temp = { mPosition.x + mOffset, mPosition.y };
        return temp;
    }

    int GetRadius() {
        return mRadius;
    }
};

class SDL_Snowfall : public SDL_Framework
{
private:
    std::vector<Snowflake*> mSnowflakeList;
    Vector2D mGravity = { 0.0, 0.3 };

public:
    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color_
        SDL_RenderClear(Renderer());
        
        if (mSnowflakeList.size() < 400) {
            int x = rand() % WindowWidth();
            int y = (rand() % WindowHeight()) * -1;
            Snowflake *snowflake = new Snowflake(x, y);
            mSnowflakeList.push_back(snowflake);
        }

        for each (auto &snowflake in mSnowflakeList)
        {
            snowflake->ApplyForce(mGravity);
            snowflake->UpdatePosition();
            SDL_Point center = { snowflake->GetPosition().IntX(), snowflake->GetPosition().IntY() };
            DrawCircle(center, snowflake->GetRadius(), { 255, 255, 255, 255 }, true);
        }

        for (int i = (int)mSnowflakeList.size() - 1; i >= 0; i--) {
            Snowflake *snowflake = mSnowflakeList[i];
            if (snowflake->GetPosition().y > WindowHeight()) {
                mSnowflakeList.erase(mSnowflakeList.begin() + i);
            }
        }

        return true;
    }
};

void RunSnowfallSimulation(void)
{
    SDL_Snowfall snowfall;
    if (snowfall.Init("Snowfall Simulation", 400, 100, 1200, 800, 0)) {
        snowfall.Run();
    }
}



