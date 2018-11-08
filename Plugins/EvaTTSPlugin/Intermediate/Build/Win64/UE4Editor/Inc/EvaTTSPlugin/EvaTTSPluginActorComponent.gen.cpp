// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EvaTTSPlugin/Public/EvaTTSPluginActorComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEvaTTSPluginActorComponent() {}
// Cross Module References
	EVATTSPLUGIN_API UClass* Z_Construct_UClass_UEvaTTSPluginActorComponent_NoRegister();
	EVATTSPLUGIN_API UClass* Z_Construct_UClass_UEvaTTSPluginActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_EvaTTSPlugin();
	EVATTSPLUGIN_API UFunction* Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
// End Cross Module References
	void UEvaTTSPluginActorComponent::StaticRegisterNativesUEvaTTSPluginActorComponent()
	{
		UClass* Class = UEvaTTSPluginActorComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "MakeObject", &UEvaTTSPluginActorComponent::execMakeObject },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics
	{
		struct EvaTTSPluginActorComponent_eventMakeObject_Parms
		{
			UClass* ObjectClass;
			UObject* CreatedObject;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CreatedObject;
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_ObjectClass;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::NewProp_CreatedObject = { UE4CodeGen_Private::EPropertyClass::Object, "CreatedObject", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000180, 1, nullptr, STRUCT_OFFSET(EvaTTSPluginActorComponent_eventMakeObject_Parms, CreatedObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::NewProp_ObjectClass = { UE4CodeGen_Private::EPropertyClass::Class, "ObjectClass", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(EvaTTSPluginActorComponent_eventMakeObject_Parms, ObjectClass), Z_Construct_UClass_UObject_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::NewProp_CreatedObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::NewProp_ObjectClass,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "TextToSpeech" },
		{ "DisplayName", "Make Object" },
		{ "Keywords", "Make Object from class" },
		{ "ModuleRelativePath", "Public/EvaTTSPluginActorComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEvaTTSPluginActorComponent, "MakeObject", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04420401, sizeof(EvaTTSPluginActorComponent_eventMakeObject_Parms), Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UEvaTTSPluginActorComponent_NoRegister()
	{
		return UEvaTTSPluginActorComponent::StaticClass();
	}
	struct Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_EvaTTSPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UEvaTTSPluginActorComponent_MakeObject, "MakeObject" }, // 743954461
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "EvaTTSPluginActorComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/EvaTTSPluginActorComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEvaTTSPluginActorComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::ClassParams = {
		&UEvaTTSPluginActorComponent::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x00B000A0u,
		FuncInfo, ARRAY_COUNT(FuncInfo),
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UEvaTTSPluginActorComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UEvaTTSPluginActorComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UEvaTTSPluginActorComponent, 2023974410);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UEvaTTSPluginActorComponent(Z_Construct_UClass_UEvaTTSPluginActorComponent, &UEvaTTSPluginActorComponent::StaticClass, TEXT("/Script/EvaTTSPlugin"), TEXT("UEvaTTSPluginActorComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEvaTTSPluginActorComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
