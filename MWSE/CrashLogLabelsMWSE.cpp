#include "CrashLogger.hpp"
#include "CrashLogFormatter.hpp"

#include "TES3Defines.h"

namespace CrashLogger::Labels {
	void FillMWSELabels() {
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BaseObject, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Alchemy, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicEffect, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Enchantment, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Ingredient, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Spell, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Script, As<TES3::Script>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Activator, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MobileActor, As<TES3::MobileObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MobileObject, As<TES3::MobileObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Class, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Alchemy, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Apparatus, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Armor, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Class);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CreatureBase);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MobileCreature, As<TES3::MobileObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Faction);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Weapon);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::LandTexture);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::LeveledCreature);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::LeveledItem);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Lockpick);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NPCBase);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NPCInstance);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Object);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Book);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Cell);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Clothing);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ContainerBase);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ContainerInstance);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Door);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Light);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Miscellaneous);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Static);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::PathGrid, As<TES3::PathGrid>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Quest);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Race);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Region);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Skill);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Sound);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Dialogue);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DialogueInfo);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherSnow);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherBase);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherBlight);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherAshstorm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherBlizzard);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherClear);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherCloudy);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherFog);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherRain);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeatherOvercast);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::AIPackageBase, As<TES3::BaseObject>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AIPackageEscort);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AIPackageActivate);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AIPackageFollow);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AIPackageTravel);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AIPackageWander);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::Reference, As<TES3::Reference>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MobilePlayer, As<TES3::MobileObject>);




		/*
		// Ni
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiNode, As<NI::Node>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiObjectNET, As<NiObjectNET>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiExtraData, As<NiExtraData>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiTriStrips, As<NiTriStrips>);
		// NiProperty
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiVertexColorProperty);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiWireframeProperty);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiZBufferProperty);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiAlphaProperty);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiStencilProperty);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiRendererSpecificProperty);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::SkyShaderProperty);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DistantLODShaderProperty);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::TallGrassShaderProperty);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::SpeedTreeFrondShaderProperty);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFogProperty);

		// unk
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraRefractionProperty);

		// NiTexture
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9Direct3DTexture);

		// NiAVObject
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPointLight);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTreeNode);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SceneGraph);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTempNode);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTempNodeManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSClearZNode);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFadeNode); // missing RTTI name
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenNiNode);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiBillboardNode);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ShadowSceneNode); // 10ADCE0

		// NiGeometry
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSScissorTriShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiParticleSystem);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiMeshParticleSystem);

		// NiRenderer
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9Renderer);

		// Misc
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkCollisionObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeaponObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkPCollisionObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkSPCollisionObject);

		// Animations

		// NiTimeController
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSDoorHavokController);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSPlayerDistanceCheckController);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DController);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysModifierCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysModifierBoolCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysModifierActiveCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysModifierFloatCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysInitialRotSpeedVarCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysInitialRotSpeedCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysInitialRotAngleVarCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysInitialRotAngleCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysGravityStrengthCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysFieldMaxDistanceCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysFieldMagnitudeCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysFieldAttenuationCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterSpeedCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterPlanarAngleVarCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterPlanarAngleCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterLifeSpanCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterInitialRadiusCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterDeclinationVarCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterDeclinationCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysAirFieldSpreadCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysAirFieldInheritVelocityCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysAirFieldAirFrictionCtlr);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysUpdateCtlr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysResetOnLoopCtlr);

		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkAvoidBox);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkSerializable);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkEntity);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkRigidBody);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkLimitedHingeConstraint);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkAction);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkUnaryAction);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkWorldObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkPhantom);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkShapePhantom);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkSimpleShapePhantom);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkPointToPathConstraint);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkPoweredHingeConstraint);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkTransformShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkSphereRepShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkConvexShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkSphereShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkCapsuleShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkMultiSphereShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkBvTreeShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkTriSampledHeightFieldBvTreeShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkCharacterListenerArrow);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkCharacterListenerSpell);

		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::ObjectExtraData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenAnimationData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenModelExtraData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenBaseMorphExtraData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DebugTextExtraData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiFloatExtraData);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::FadeNodeMaxAlphaExtraData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiBinaryExtraData);

		// Geometry data
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiAdditionalGeometryData, nullptr);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSPackedAdditionalGeometryData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiMeshPSysData);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiTask, nullptr);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTECreateTask);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiParallelUpdateTaskManager::SignalTask);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysUpdateTask);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiSkinInstance);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysMeshUpdateModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysRotationModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitter);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysMeshEmitter);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysVolumeEmitter);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysCylinderEmitter);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysSphereEmitter);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysBoxEmitter);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysGravityModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysSpawnModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysPositionModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysGrowFadeModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysDragModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysColorModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysColliderManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysBoundUpdateModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysBombModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysAgeDeathModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysVortexFieldModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysTurbulenceFieldModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysRadialFieldModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysGravityFieldModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysDragFieldModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysAirFieldModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysEmitterCtlrData);
		//		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSShaderAccumulator);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysCollider);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysSphericalCollider);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysPlanarCollider);


		// NiStream
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSStream);


		// animations
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSAnimGroupSequence);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AnimSequenceBase);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AnimSequenceSingle);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AnimSequenceMultiple);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedKF, As<QueuedKF>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedAnimIdle);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFile), As<BSFile>;
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ArchiveFile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CompressedArchiveFile);

		// model
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Model), As<TESModel>;
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedModel, As<QueuedModel>);

		// effects
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ScriptEffect, As<ScriptEffect>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ActiveEffect, As<ActiveEffect>);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AbsorbEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AssociatedItemEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BoundItemEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CalmEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ChameleonEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CommandCreatureEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CommandEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CommandHumanoidEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CureEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DarknessEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DemoralizeEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DetectLifeEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DisintegrateArmorEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DisintegrateWeaponEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::DispelEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::FrenzyEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::InvisibilityEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::LightEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::LockEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicHitEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicModelHitEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicShaderHitEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NightEyeEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::OpenEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ParalysisEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ReanimateEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ShieldEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SummonCreatureEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SunDamageEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::TelekinesisEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::TurnUndeadEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ValueModifierEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::VampirismEffect);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicItem, nullptr);

		// w
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Archive);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Atmosphere);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AttachDistant3DTask);


		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSCullingProcess);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSExtraData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenImage);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenKeyframe);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenKeyframeMultiple);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenModel);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenModelMap);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenMorph);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenMorphDataHair);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenMorphDataHead);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSFaceGenMorphStatistical);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSSearchPath);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTaskThread);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTempEffect);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTempEffectGeometryDecal);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTempEffectParticle);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSThread);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BSTreeModel);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BackgroundCloneThread);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BaseExtraList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BlendSettingCollection);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::CBillboardLeaf);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CIdvCamera);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CTreeEngine);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CellMopp);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ChangesMap);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Clouds);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::CombatController);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::EffectItemList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExteriorCellLoaderTask);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExteriorCellNewReferencesMap);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraAction);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraAnim);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCannotWear);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCell3D);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCellCanopyShadowMask);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCellClimate);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCellMusicType);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCellWaterType);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCharge);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraContainerChanges);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraCount);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraDataList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraDetachTime);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraDistantData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraDroppedItemList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraEditorID);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraEditorRefMoveData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraEnableStateChildren);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraEnableStateParent);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraFollower);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraGhost);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraGlobal);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraHasNoRumors);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraHavok);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraHeadingTarget);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraHealth);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraHotkey);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraInfoGeneralTopic);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraItemDropper);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraLastFinishedSequence);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraLevCreaModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraLeveledCreature);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraLeveledItem);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraLight);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraMapMarker);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraMerchantContainer);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraNorthRotation);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraOriginalReference);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraOwnership);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraPackage);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraPackageStartLocation);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraPersistentCell);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraPoison);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraProcessMiddleLow);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraRagDollData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraRandomTeleportMarker);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraRank);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraReferencePointer);


		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraRegionList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraRunOncePacks);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraScale);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraScript);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraSeed);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraSeenData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraSound);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraStartingPosition);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraStartingWorldOrCell);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraTeleport);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraTimeLeft);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraTresPassPackage);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraUsedMarkers);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraUses);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraWorn);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraWornLeft);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ExtraXTarget);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::GridArray);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::GridCellArray);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::HavokError);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::HavokFileStreambufReader);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::HavokStreambufFactory);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::IOManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::IOTask);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::IntSeenData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::InteriorCellNewReferencesMap);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::LipTask);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicBallProjectile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicBoltProjectile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicCaster);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicFogProjectile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicProjectile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicSprayProjectile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MagicTarget);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::MessageHandler);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Moon);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiBinaryStream);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DDefaultShader);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DGeometryGroupManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DHLSLPixelShader);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DHLSLVertexShader);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DPass);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DPixelShader);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DRenderState);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShader);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderConstantManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderDeclaration);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderFactory);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderInterface);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderProgram);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderProgramCreator);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderProgramCreatorAsm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderProgramCreatorHLSL);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderProgramCreatorObj);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DShaderProgramFactory);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiD3DVertexShader);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX92DBufferData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9AdditionalDepthStencilBufferData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9DynamicTextureData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9ImplicitBufferData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9ImplicitDepthStencilBufferData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9IndexBufferManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9RenderState);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9RenderedCubeMapData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9RenderedTextureData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9ShaderConstantManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9ShaderDeclaration);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9SourceCubeMapData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9SourceTextureData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9TextureBufferData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9TextureData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9TextureManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDX9VertexBufferManager);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiDynamicGeometryGroup);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiFile);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiGeometryGroup);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiMemStream);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiPSysFieldModifier);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiRefObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiSearchPath);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiStaticGeometryGroup);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NiUnsharedGeometryGroup);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::NonActorMagicCaster);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NonActorMagicTarget);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Normal);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::NumericIDBufferMap);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::PosGen);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Precipitation);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedChildren);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedFile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedFileEntry);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedHead);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedHelmet);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedMagicItem);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedTree);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedTreeBillboard);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::QueuedTreeModel);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::Random);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegSettingCollection);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SeenData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Sky);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SkyObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SkyTask);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SpecificItemCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Stars);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Sun);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AIForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ActorBaseData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AnimGroup);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Animation);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ArrowTargetListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::AttackDamageForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Attributes);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::BipedModelForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ChildCell);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Container);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Description);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::EnchantableForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::FullName);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::HealthForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::IconTree);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::LeveledList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ModelAnim);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ModelList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ModelTree);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ObjectLAND);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ProduceForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RaceForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ReactionForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionData);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionDataGrass);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionDataLandscape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionDataManager);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionDataMap);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionDataSound);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionDataWeather);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionGrassObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionGrassObjectList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::RegionList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ScriptableForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SoundFile);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::SpellList);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::TrapListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::ValueForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WaterListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WeightForm);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::WindListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::TopicInfoArray);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::Uniform);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkCharacterListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkEntityListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkTelekinesisListener);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkBaseObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkConstraintCinfo);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkLimitedHingeConstraintCinfo);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkReferencedObject);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpAllCdBodyPairCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpAllCdPointCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpAllRayHitCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpBoxShape);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpBroadPhaseCastCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpCdBodyPairCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpCdPointCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkClosestRayHitCollector);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpEntityActivationListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpEntityListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpPhantomListener);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpRayHitCollector);

		Push(TES3::VirtualTableAddress::VirtualTableAddress::bhkWorldObject);
		Push(TES3::VirtualTableAddress::VirtualTableAddress::hkpAabbPhantom); */
	};
}