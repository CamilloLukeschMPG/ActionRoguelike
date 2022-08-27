// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SInteractionComponent.h"

#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ASCharacter::SpawnProjectile_TimeElapsed, Cast<UClass>(AttackProjectileClass));
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnProjectile, Delegate, 0.2f, false);
}

void ASCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);

	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ASCharacter::SpawnProjectile_TimeElapsed, Cast<UClass>(DashProjectileClass));
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnProjectile, Delegate, 0.2f, false);
}

void ASCharacter::SpawnProjectile_TimeElapsed(UClass* ProjectileClass)
{
	FVector const HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + (CameraComp->GetComponentRotation().Vector() * 100000.0f);

	FHitResult Hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	FVector Target = bBlockingHit ? Hit.Location : End;

	FRotator Rot = UKismetMathLibrary::Conv_VectorToRotator(Target - HandLocation);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	DrawDebugLine(GetWorld(), CameraComp->GetComponentLocation(), CameraComp->GetComponentLocation() + CameraComp->GetComponentRotation().Vector() * 100000.0f, LineColor, false, 4.0f, 0, 1.0f);
	DrawDebugLine(GetWorld(), HandLocation, HandLocation + CameraComp->GetComponentRotation().Vector() * 10000.0f, FColor::Yellow, false, 4.0f, 0, 2.0f);
	DrawDebugLine(GetWorld(), HandLocation, Target, FColor::White, false, 4.0f, 0, 2.0f);

	FTransform const SpawnTM = FTransform(Rot, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}


void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASCharacter::Dash);

}

