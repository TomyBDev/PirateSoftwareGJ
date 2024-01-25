// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SaveStructs.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Ability1Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Ability2Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PassiveLevel;

	FPlayerStats(int32 a1 = 1, int32 a2 = 1, int32 p = 1)
	{
		Ability1Level = a1;
		Ability2Level = a2;
		PassiveLevel = p;
	}
};

USTRUCT(BlueprintType)
struct FGraphicsSettingsStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 windowedMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 resolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 frameRateLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 viewDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 postProcessing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 antiAliasing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 textureQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 shadowQuality;


	FGraphicsSettingsStruct(int32 wm = 0, int32 r = 0, int32 frl = 0, int32 vd = 0, int32 pp = 0, int32 aa = 0, int32 tq = 0, int32 sq = 0)
	{
		windowedMode = wm;
		resolution = r;
		frameRateLimit = frl;
		viewDistance = vd;
		postProcessing = pp;
		antiAliasing = aa;
		textureQuality = tq;
		shadowQuality = sq;
	}
};

USTRUCT(BlueprintType)
struct FGameplaySettingsStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 sensitivity;


	FGameplaySettingsStruct(int32 s = 5)
	{
		sensitivity = s;
	}
};

USTRUCT(BlueprintType)
struct FAudioSettingsStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 globalVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 musicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 stxVolume;


	FAudioSettingsStruct(int32 gv = 1, int32 mv = 1, int32 sv = 1)
	{
		globalVolume = gv;
		musicVolume = mv;
		stxVolume = sv;
	}
};