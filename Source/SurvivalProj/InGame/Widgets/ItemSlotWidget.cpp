// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"


void UItemSlotWidget::SlotUpdate(FItemSlotData SlotData)
{
	ItemImage->SetBrushFromTexture(SlotData.IconTexture);
	// int를 text로 바꿔서 인입.
	ItemQuantityText->SetText(FText::AsNumber(SlotData.Quantity));
	ItemId = SlotData.ItemId;
	ItemImage->SetVisibility(ESlateVisibility::Visible);
	ItemQuantityText->SetVisibility(ESlateVisibility::Visible);
	SlotIndex = SlotData.SlotNumber;
	ItemType = SlotData.ItemType;

}

void UItemSlotWidget::SlotRemove()
{
	ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	ItemQuantityText->SetVisibility(ESlateVisibility::Collapsed);

	ItemImage->SetBrushFromTexture(nullptr);
	ItemQuantityText->SetText(FText::GetEmpty());

	ItemId = NAME_None;
	SlotIndex = 0;

}

void UItemSlotWidget::SpawnActPopup()
{
	/*AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (!PC || !PopupClass) return;

	// 1. 단일 싱글톤 팝업 사출 공정 가동 (앞서 마감한 HUD의 단일 생성 포트 타격)
	AMyHUD* MyHUD = Cast<AMyHUD>(PC->GetHUD());
	if (!MyHUD) return;

	// 2. 팝업창 인스턴스를 우선 청정 구체화
	UItemActSelector* NewPopup = CreateWidget<UItemActSelector>(PC, PopupClass);

	if (NewPopup)
	{
		]
		// 생성된 팝업창의 장부를 열고 "너의 소유자는 나(this)다!"라고 주소록 포인터를 강제 기입!
		NewPopup->OwningSlotWidget = this;

		// 3. 주권 결착이 완료된 청정 팝업 위젯을 HUD 사령탑을 통해 뷰포트에 최종 안착
		MyHUD->RegisterAndDisplayPopup(NewPopup);
	}*/
}

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
		ItemQuantityText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

/*FReply UItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return Reply.NativeReply;
}

void UItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// 1. 순정 드래그 드롭 오퍼레이션 자산 개설
	UDragDropOperation* DragOp = NewObject<UDragDropOperation>(this);

	// 2. [안전 주소록 박제]: 단순 포인터이므로 본인(this)을 Payload에 박아도 안전하다.
	DragOp->Payload = this;

	// 3. 비주얼 증발 버그 원천 소독: 내 형태를 복제한 가벼운 유령 껍데기 위젯을 가설한다.
	if (DragVisualClass)
	{
		UUserWidget* DragVisual = CreateWidget<UUserWidget>(this, DragVisualClass);
		if (DragVisual)
		{
			// 이곳에서 유령 위젯 내부의 아이템 이미지와 수량을 내 현재 데이터와 동치 갱신한다.
			// DragVisual->UpdateInfo(this->ItemId, this->CurrentCount);
			DragOp->DefaultDragVisual = DragVisual;
		}
	}

	// 4. 엔진 커널로 데이터 바구니 패킷 송신
	OutOperation = DragOp;
}

bool UItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{// 인입된 패킷 주머니 무결성 불시검문
	if (InOperation == nullptr || InOperation->Payload == nullptr)
	{
		return false;
	}

	// 1. 공중에 날아다니던 Payload 장부를 열어 출발지 슬롯의 램 주소를 역산 인출
	UItemSlotWidget* SourceSlot = Cast<UItemSlotWidget>(InOperation->Payload);
	if (SourceSlot == nullptr) 
	{ 
		return false;
	}

	// 2. 0비트 오차로 출발지와 목적지(this)의 방 번호 파싱
	int32 FromIndex = SourceSlot->SlotIndex;
	int32 ToIndex = this->SlotIndex;

	// 제자리에 그대로 던졌다면 연산 낭비 차단을 위해 소독 기각
	if (FromIndex == ToIndex)
	{
		return false;
	}

	// 3. [최종 하이엔드 공정: 플레이어 사령탑 컴포넌트 밸브 타격]
	// 이전 전선에서 배운 로컬 컨트롤러 및 소유권 체인을 역산 가동하여 서버 RPC 포트로 직격 사격한다.
	APawn* OwningPawn = GetOwningPlayerPawn();
	if (OwningPawn)
	{
		// UInventoryComponent* InvComp = OwningPawn->FindComponentByClass<UInventoryComponent>();
		// if (InvComp) { InvComp->ServerMoveItem(FromIndex, ToIndex); }
		return true;
	}

	return false;
}*/

