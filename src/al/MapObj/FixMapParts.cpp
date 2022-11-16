#include "al/MapObj/FixMapParts.h"
#include "al/sensor/SensorMsg.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/OtherUtil.h"
#include "al/util/StageSwitchUtil.h"

namespace al {

FixMapParts::FixMapParts(const char* name) : LiveActor(name) {}

void FixMapParts::init(const ActorInitInfo& info) {
    const char* suffix = nullptr;
    tryGetStringArg(&suffix, info, "Suffix");
    initMapPartsActor(this, info, suffix);
    trySyncStageSwitchAppearAndKill(this);
    registActorToDemoInfo(this, info);

    if (mModelKeeper != nullptr && !isExistAction(this) && !isViewDependentModel(this)) {
        mStatic = true;
    }
}

void FixMapParts::appear() {
    LiveActor::appear();

    if (isExistModel(this))
        tryStartAction(this, "Appear");
}

void FixMapParts::movement() {
    if (!mStatic)
        LiveActor::movement();
}

void FixMapParts::calcAnim() {
    if (!mStatic)
        LiveActor::calcAnim();
    else
        calcViewModel(this);
}

bool FixMapParts::receiveMsg(const SensorMsg* message, HitSensor* source, HitSensor* target) {
    if (isMsgAskSafetyPoint(message))
        return !isValidSwitchAppear(this) && !isValidSwitchKill(this);

    if (isMsgShowModel(message)) {
        showModelIfHide(this);
        return true;
    }

    if (isMsgHideModel(message)) {
        hideModelIfShow(this);
        return true;
    }

    return false;
}

}  // namespace al
