// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "Components/ProgressBar.h"


void UHPBarWidget::HPBarUpdate(float MaxHp, float CurrentHp)
{
	// MaxHp가 0 이하일 경우 나누기 연산(Divide by Zero) 크래시가 터지므로 원천 차단
	if (MaxHp <= 0.0f)
	{
		HPProgressBar->SetPercent(0.0f);
		return;
	}

	float HPPercent = CurrentHp / MaxHp;

	HPPercent = FMath::Clamp(HPPercent, 0.0f, 1.0f);

	HPProgressBar->SetPercent(HPPercent);

}


void UHPBarWidget::NativeConstruct()
{
}

void UHPBarWidget::NativeOnInitialized()
{
}
