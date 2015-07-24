// Fill out your copyright notice in the Description page of Project Settings.

#include "JustDoIT.h"
#include "JustDoITCorporation.h"


UJustDoITCorporation::UJustDoITCorporation () {
	TotalMoneyEarned = 0;
}

void UJustDoITCorporation::EarnSomeMoney (const float& money) {
	TotalMoneyEarned += money;
	//todo update money chart 
}
