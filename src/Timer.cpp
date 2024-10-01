#include <Timer.h>
#include <Command.h>
#include <Motor.h>
#include <Light.h>

bool sparkingLight [7][3] = {0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1};

cycle cyc;
extern Motor *fanCtrl;
extern RGB *rgbDin, *rgbMainBed, *rgbSubBed, *rgbWash;

// 计时器函数
void cycling() {
    if (cyc.doorOpenTime > 0) {
        if (!--cyc.doorOpenTime) {
            cmdDoor(false);
        }
    }

    if (cyc.fanAngle >= 0) {
        cyc.fanAngle += 5;
        if(cyc.fanAngle > 180)cyc.fanAngle = 0;
        fanCtrl->angle(cyc.fanAngle);
    }

    if(cyc.DinLight >= 0) {
        if(++cyc.DinLight >= 7)cyc.DinLight = 0;
        rgbDin->On(sparkingLight[cyc.DinLight][0], sparkingLight[cyc.DinLight][1], sparkingLight[cyc.DinLight][2]);
    }
    if(cyc.MBLight >= 0) {
        if(++cyc.MBLight >= 7)cyc.MBLight = 0;
        rgbMainBed->On(sparkingLight[cyc.MBLight][0], sparkingLight[cyc.MBLight][1], sparkingLight[cyc.MBLight][2]);
    }
    if(cyc.SBLight >= 0) {
        if(++cyc.SBLight >= 7)cyc.SBLight = 0;
        rgbSubBed->On(sparkingLight[cyc.SBLight][0], sparkingLight[cyc.SBLight][1], sparkingLight[cyc.SBLight][2]);
    }
    if(cyc.WSLight >= 0) {
        if(++cyc.WSLight >= 7)cyc.WSLight = 0;
        rgbWash->On(sparkingLight[cyc.WSLight][0], sparkingLight[cyc.WSLight][1], sparkingLight[cyc.WSLight][2]);
    }
}