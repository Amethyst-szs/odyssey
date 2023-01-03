#include <al/Library/Layout/LayoutPartsActorKeeper.h>
#include <al/Library/Layout/LayoutActor.h>

namespace al {
void LayoutPartsActorKeeper::resisterPartsActor(al::LayoutActor* actor) {

}
void LayoutPartsActorKeeper::appear() {
    for (s32 i = 0; i < mNumActors; i++) {
        mPartsActors[i]->appear();
    }
}
void LayoutPartsActorKeeper::calcAnim(bool recursive) {
    for (s32 i = 0; i < mNumActors; i++) {
        mPartsActors[i]->calcAnim(recursive);
    }
}
LayoutPartsActorKeeper::LayoutPartsActorKeeper(s32 maxActors) : mMaxActors(maxActors) {
    mPartsActors = new al::LayoutActor*[maxActors];
}
}  // namespace al
