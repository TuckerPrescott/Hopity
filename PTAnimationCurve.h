#ifndef PTANIMATIONCURVE_H
#define PTANIMATIONCURVE_H

#include "cocos2d.h"

USING_NS_CC;

typedef struct
{
    float	hdl1;
    CCPoint	knot;
    float	hdl2;

} bez3;

typedef enum
{
    PTAnimationCurveInterpolationConstant = 0,
    PTAnimationCurveInterpolationLinear,
    PTAnimationCurveInterpolationBizer

} PTAnimationCurveInterpolationType;

typedef enum
{
    PTAnimationCurveExtrapolationConstant = 0,
    PTAnimationCurveExtrapolationExtrapolation,
    PTAnimationCurveExtrapolationCyclic,
    PTAnimationCurveExtrapolationCyclicExtrapolation

} PTAnimationCurveExtrapolationType;


class PTAnimationCurve
{
public:
    static PTAnimationCurve *nullCurve();
    static PTAnimationCurve *linearCurve();
    static PTAnimationCurve *easeInCurve();
    static PTAnimationCurve *easeOutCurve();
    static PTAnimationCurve *elasticInCurve();

    enum AnimationCurveType {
        Linear = 0,
        EasyIn,
        EasyOut,
        ElasticIn,
        Custom,
        Null
    };

    PTAnimationCurve();

    PTAnimationCurve *duplicated();

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();

    PTAnimationCurveExtrapolationType extrapolation;
    PTAnimationCurveInterpolationType interpolation;

    float time;
    AnimationCurveType preset();

    int pointIndex( float time );
    bez3 point( int index );
    void setPoint(int, bez3);

    void setPointValue( int, CCPoint );
    CCPoint pointValue( int );

    void setHandler1Value( int, float );
    float handler1Value(int);

    void setHandler2Value( int, float );
    float handler2Value(int);

    int pointsNumber();

    void updated(float dt);
    float cubicBezier(float t, float a, float b, float c, float d);
    void calculateRatio();
    void reset();
    void setPoints( bez3 *points );
    void setValue(float _value, float _time);
    float value(float _time);
    float value();
    void removePoint(float _time);
    void removePointAtIndex( int );

    std::vector<int> keyFrameMarkers();

    // return true if A has time bigger than B
    bool needSwap( int a, int b );
    void swapPoints( int, int );

private:
    float tRatio;
    float vRatio;
    float tvRatio;
    int currentPoint;
    float deltaTime;
    bez3 *pPoints;
    unsigned int pNumberOfPoints;
    float pValue;

    AnimationCurveType _preset;
};

#endif // PTANIMATIONCURVE_H
