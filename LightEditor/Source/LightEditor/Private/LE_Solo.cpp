#include "LE_Solo.h"
#define LOCTEXT_NAMESPACE "Synaptech"

TArray<TWeakObjectPtr<ALight>>SLE_Solo::ActiveList;

void SLE_Solo::Construct(const FArguments &InArgs, ALight* Target) {
	Item = Target;	
	SImage::Construct(
		SImage::FArguments()
		.Image(this, &SLE_Solo::GetBrush)
	);
}

void SLE_Solo::SetSolo(const bool DoSolo) {
	if (Item.IsStale()) { Solo = false; return; }
	bool WasSolo = Solo; Solo = DoSolo;
	
	if (Solo) {
		SLE_Solo::ActiveList.Empty();
		
		auto World = Item.Get()->GetWorld();
		for (TActorIterator<ALight>Actor(World); Actor; ++Actor) {
			if ((*Actor)->HasAnyFlags(RF_BeginDestroyed)) { continue; }
			if ((*Actor) == Item.Get()) { continue; }			
			if (Actor->GetLightComponent()->bAffectsWorld) {
				SLE_Solo::ActiveList.Add(*Actor);
				SetLightActive(*Actor, false);
			}
		}
		SetLightActive(Item.Get(), true);
	}
	else if (WasSolo) {
		for (auto Actor : SLE_Solo::ActiveList) {
			if (Actor.IsStale()) { continue; }
			SetLightActive(Actor.Get(), true);
		}
	}
	else { Solo = false; }
}

void SLE_Solo::SetLightActive(ALight* Target, const bool Active) {
	FPropertyChangedEvent PropEditEvent(ULightComponent::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(ULightComponent, bAffectsWorld)));
	EComponentMobility::Type Mobility = Target->GetLightComponent()->Mobility;
	uint32 AffectsWorld = (Active) ? 1 : 0;
	//
	Target->Modify();
	Target->GetLightComponent()->Mobility = EComponentMobility::Stationary;
	Target->GetLightComponent()->bAffectsWorld = AffectsWorld;
	Target->GetLightComponent()->InvalidateLightingCache();
	Target->GetLightComponent()->MarkRenderStateDirty();
	//
	Target->GetLightComponent()->PostEditChangeProperty(PropEditEvent);
	Target->GetLightComponent()->Mobility = Mobility;
}


#undef LOCTEXT_NAMESPACE
