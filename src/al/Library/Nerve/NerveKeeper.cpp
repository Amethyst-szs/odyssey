#include <al/Library/Nerve/NerveKeeper.h>
#include <al/Library/Nerve/Nerve.h>
#include <al/Library/Nerve/NerveStateCtrl.h>

namespace al {
NerveKeeper::NerveKeeper(al::IUseNerve* parent, const al::Nerve* nerve, s32 maxStates) : mParent(parent), mNextNerve(nullptr) {
    if (maxStates > 0) {
        mStateCtrl = new NerveStateCtrl(maxStates);
    }
}
void NerveKeeper::initNerveAction(al::NerveActionCtrl* actionCtrl) {
    mActionCtrl = actionCtrl;
}
void NerveKeeper::setNerve(const al::Nerve* nextNerve) {
    if (mStep >= 0 && mCurrentNerve != nullptr)
        mCurrentNerve->executeOnEnd(this);

    mNextNerve = nextNerve;
    mStep = -1;
}

void NerveKeeper::tryChangeNerve() {
    if (mNextNerve) {
        if (mStateCtrl) {
            mStateCtrl->tryEndCurrentState();
            mStateCtrl->startState(mNextNerve);
        }
        mCurrentNerve = mNextNerve;
        mNextNerve = nullptr;
        mStep = 0;
    }
}
void NerveKeeper::update() {
    tryChangeNerve();
    mCurrentNerve->execute(this);
    mStep++;
    tryChangeNerve();
}
const al::Nerve* NerveKeeper::getCurrentNerve() const {
    return mNextNerve ? mNextNerve : mCurrentNerve;
}

}  // namespace al
