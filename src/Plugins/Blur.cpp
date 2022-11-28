#include "Blur.hpp"
#include <cmath>
#include <iostream>
#include <numbers>
using namespace bp;

void Blur::onMousePress(const bp::MouseButtonEventData* e)
{
    sharpening_ = e->ctrl;
    Pen::onMousePress(e);
} 

void Blur::buildSetupWidget()
{
    Pen::buildSetupWidget();
    Scrollbar* sb = createScrollbar(5, 70, 100, 15, 10, 4);
    sb->valueChanged.connect(this, &Blur::setSigma);
    createLabel(110, 67, 50, 21, "Sigma");

    sb = createScrollbar(5, 90, 100, 15, 500, 50);
    sb->valueChanged.connect(this, &Blur::setDegree);
    createLabel(110, 87, 50, 21, "Sharpening degree");

}

extern "C" void init_module()
{
    booba::addTool(new Blur);
}

void Blur::applyTool(const Brush::BrushPoint& pt)
{
    if(pixarr_.get(pt.point.x, pt.point.y)) return;
    pixarr_.set(pt.point.x, pt.point.y);

    // std::cerr << "Overrided\n";

    double rAvg = 0, gAvg = 0, bAvg = 0, summ =0;

    for(int dx = -sigma_ * SIGMA_LIMIT; dx <= sigma_ * SIGMA_LIMIT; ++dx)
    {
        for(int dy = -sigma_ * SIGMA_LIMIT; dy <= sigma_ * SIGMA_LIMIT; ++dy)
        {
            Point point = {pt.point.x + dx, pt.point.y + dy};
            if(!isOnImage(image_, point)) point = pt.point;

            Color col = image_->getPixel(point.x, point.y);
            rAvg += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy] * col.rf();
            gAvg += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy] * col.gf();
            bAvg += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy] * col.bf();
            summ += gayss_[dx < 0 ? -dx : dx][dy < 0 ? -dy : dy];
            // std::cerr << dx << " " << dy << gayss_[abs(dx)][abs(dy)] << '\n';
        }
    }

    rAvg /= summ;
    bAvg /= summ;
    gAvg /= summ;

    Color colorAvg = image_->getPixel(pt.point.x, pt.point.y);
    if(!sharpening_)
    {
        colorAvg.rf(rAvg);
        colorAvg.bf(bAvg);
        colorAvg.gf(gAvg);
        // image_->putPixel(pt.point.x, pt.point.y, 0);
    }
    else {
        colorAvg.rf(std::max(0.,std::min(1., (colorAvg.rf() - rAvg) * degee_ / 10 + rAvg)));
        colorAvg.gf(std::max(0.,std::min(1., (colorAvg.gf() - gAvg) * degee_ / 10 + gAvg)));
        colorAvg.bf(std::max(0.,std::min(1., (colorAvg.bf() - bAvg) * degee_ / 10 + bAvg)));
    }
    apply_.push_back({pt.point, colorAvg}); 
}

void Blur::brushDraw(const Point& pt)
{
    apply_.clear();
    Pen::brushDraw(pt);

    for(auto [point, col] : apply_)
    {
        image_->putPixel(point.x, point.y, col);
    }
}


void Blur::fillGayss()
{
    double sigma = sigma_;
    gayss_.resize(SIGMA_LIMIT * sigma_ + 1);
    for(size_t x = 0; x <= SIGMA_LIMIT * sigma_; ++x)
    {
        gayss_[x].resize(SIGMA_LIMIT * sigma_ + 1);
        for(size_t y = 0; y <= SIGMA_LIMIT * sigma_; ++y)
        {
            gayss_[x][y] = std::exp(-static_cast<double>(x*x + y*y) / (2 * sigma * sigma)) / (2 * std::numbers::pi * sigma * sigma);
            // std::cerr << x << " " << y << " " << gayss_[x][y] << '\n';
        }
    }
}

void Blur::setSigma(int sigma)
{
    sigma_ = sigma;
    fillGayss();    
}