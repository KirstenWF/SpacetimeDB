#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Credentials.generated.h"

//@TODO: Implement version where multiple tokens can be stored, e.g. for testing multiple play sesstions on same unreal instance.


/**
 * Credentials class for managing authentication tokens in SpacetimeDB.
 * This class provides methods to initialize the credential system, load a token,
 * and save a token using Unreal Engine's Blueprint system.
 */
UCLASS()
class SPACETIMEDBSDK_API UCredentials : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Initialize the credential system.  InFilename mimics the C# API but is
     * used as a key within the config file rather than an actual filename.
     */
    UFUNCTION(BlueprintCallable, Category = "SpacetimeDB|Credentials")
    static void Init(const FString& InFilename);

    /** Load a previously stored token. */
    UFUNCTION(BlueprintCallable, Category = "SpacetimeDB|Credentials")
    static FString LoadToken();

    /** Persist a token for later retrieval. */
    UFUNCTION(BlueprintCallable, Category = "SpacetimeDB|Credentials")
    static void SaveToken(const FString& InToken);

	/** Load a previously stored token based on StoredKey, not requiring Init() call. */
	UFUNCTION(BlueprintCallable, Category = "SpacetimeDB|Credentials")
	static FString LoadTokenWithKey(const FString& InStoredKey);

	/** Persist a token with StoredKey for later retrieval, not requiring Init() call. */
	UFUNCTION(BlueprintCallable, Category = "SpacetimeDB|Credentials")
	static void SaveTokenWithKey(const FString& InStoredKey, const FString& InToken);

private:
	/** Currently loaded authentication token */
	static FString Token;

    /** Key used when storing the token via the config system */
    static FString StoredKey;
};
