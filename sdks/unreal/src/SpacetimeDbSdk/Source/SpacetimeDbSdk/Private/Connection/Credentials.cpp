#include "Connection/Credentials.h"
#include "Connection/LogCategory.h"
#include "Misc/Paths.h"
#include "Misc/ConfigCacheIni.h"

FString UCredentials::Token;
FString UCredentials::StoredKey;

void UCredentials::Init(const FString& InFilename)
{
	StoredKey = InFilename;
    LoadToken();
}

FString UCredentials::LoadToken()
{
    FString LoadedValue;

    if (StoredKey.IsEmpty())
    {
        UE_LOG(LogSpacetimeDb_Connection, Warning, TEXT("UCredentials::Init has not been called before LoadToken."));
        return Token;
    }

	Token = LoadTokenWithKey(StoredKey);
	return Token;
}

FString UCredentials::LoadTokenWithKey(const FString& InStoredKey)
{
	FString LoadedValue;

	if (InStoredKey.IsEmpty())
	{
		UE_LOG(LogSpacetimeDb_Connection, Warning, TEXT("UCredentials::LoadToken: InStoredKey needs to be set!"));
		return LoadedValue;
	}

	if (GConfig->GetString(TEXT("SpacetimeDB"), *InStoredKey, LoadedValue, GGameUserSettingsIni))
	{
		UE_LOG(LogSpacetimeDb_Connection, Verbose, TEXT("UCredentials::Credentials loaded for key %s from %s."), *InStoredKey, *FPaths::GetCleanFilename(GGameUserSettingsIni));
	}
	else
	{
		UE_LOG(LogSpacetimeDb_Connection, Verbose, TEXT("UCredentials::No stored credentials found for key %s."), *InStoredKey);
	}

	return LoadedValue;
}

void UCredentials::SaveToken(const FString& InToken)
{
    if (StoredKey.IsEmpty())
    {
        UE_LOG(LogSpacetimeDb_Connection, Warning, TEXT("UCredentials::Init has not been called before SaveToken."));
        return;
    }

	Token = InToken;
	SaveTokenWithKey(StoredKey, InToken);
}

void UCredentials::SaveTokenWithKey(const FString& InStoredKey, const FString& InToken)
{
	if (InStoredKey.IsEmpty())
	{
		UE_LOG(LogSpacetimeDb_Connection, Warning, TEXT("UCredentials::SaveToken: InStoredKey needs to be set!"));
		return;
	}

	GConfig->SetString(TEXT("SpacetimeDB"), *InStoredKey, *InToken, GGameUserSettingsIni);

	// This call writes the in-memory changes to the GGameUserSettingsIni file on the disk.
	GConfig->Flush(false, GGameUserSettingsIni);
}
