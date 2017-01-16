#ifndef THREEBANDKILLEQEFFECT_H
#define THREEBANDKILLEQEFFECT_H

#include <QMap>

#include "control/controlproxy.h"
#include "effects/effect.h"
#include "effects/effectprocessor.h"
#include "engine/effects/engineeffect.h"
#include "engine/effects/engineeffectparameter.h"
#include "engine/enginefilterbiquad1.h"
#include "util/class.h"
#include "util/defs.h"
#include "util/sample.h"
#include "util/types.h"
#include "util/memory.h"

class ThreeBandKillEQEffectGroupState {
  public:
    ThreeBandKillEQEffectGroupState();
    virtual ~ThreeBandKillEQEffectGroupState();

    void setFilters(
            int sampleRate, double lowFreqCorner, double highFreqCorner);

    std::unique_ptr<EngineFilterBiquad1Peaking> m_lowBoost;
    std::unique_ptr<EngineFilterBiquad1Peaking> m_midBoost;
    std::unique_ptr<EngineFilterBiquad1Peaking> m_highBoost;
    std::unique_ptr<EngineFilterBiquad1Peaking> m_lowKill;
    std::unique_ptr<EngineFilterBiquad1Peaking> m_midKill;
    std::unique_ptr<EngineFilterBiquad1HighShelving> m_highKill;
    QList<CSAMPLE*> m_pBufs;
    double m_oldLowBoost;
    double m_oldMidBoost;
    double m_oldHighBoost;
    double m_oldLowKill;
    double m_oldMidKill;
    double m_oldHighKill;

    double m_loFreqCorner;
    double m_highFreqCorner;

    unsigned int m_oldSampleRate;
};

class ThreeBandKillEQEffect : public PerChannelEffectProcessor<ThreeBandKillEQEffectGroupState> {
  public:
    ThreeBandKillEQEffect(EngineEffect* pEffect, const EffectManifest& manifest);
    ~ThreeBandKillEQEffect() override;

    static QString getId();
    static EffectManifest getManifest();

    void setFilters(int sampleRate, double lowFreqCorner, double highFreqCorner);

    // See effectprocessor.h
    void processChannel(const ChannelHandle& handle,
                        ThreeBandKillEQEffectGroupState* pState,
                        const CSAMPLE* pInput, CSAMPLE *pOutput,
                        const unsigned int numSamples,
                        const unsigned int sampleRate,
                        const EffectProcessor::EnableState enableState,
                        const GroupFeatureState& groupFeatureState);

  private:
    ThreeBandKillEQEffect(const ThreeBandKillEQEffect&) = delete;
    void operator=(const ThreeBandKillEQEffect&) = delete;

    QString debugString() const {
        return getId();
    }

    EngineEffectParameter* m_pPotLow;
    EngineEffectParameter* m_pPotMid;
    EngineEffectParameter* m_pPotHigh;

    EngineEffectParameter* m_pKillLow;
    EngineEffectParameter* m_pKillMid;
    EngineEffectParameter* m_pKillHigh;

    std::unique_ptr<ControlProxy> m_pLoFreqCorner;
    std::unique_ptr<ControlProxy> m_pHiFreqCorner;
};

#endif // ThreeBANDKILLEQEFFECT_H
