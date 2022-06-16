// Copyright Byteyang Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "ByVSoftObjectPath.generated.h"

USTRUCT(BlueprintType)
struct FByVSoftObjectPath
{
	GENERATED_BODY()

	FByVSoftObjectPath() {}

	/** Construct from another soft object path */
	FByVSoftObjectPath(const FByVSoftObjectPath& Other)
		:SoftObjectPath(Other.SoftObjectPath) {}

	/** Construct from a moveable soft object path */
	FByVSoftObjectPath(FByVSoftObjectPath&& Other)
		:SoftObjectPath(Other.SoftObjectPath) {}

	/** Construct from a path string. Non-explicit for backwards compatibility. */
	FByVSoftObjectPath(const FString& Path)
		:SoftObjectPath(Path) {}
	explicit FByVSoftObjectPath(FWideStringView Path)
		:SoftObjectPath(Path) {}
	explicit FByVSoftObjectPath(FAnsiStringView Path)
		:SoftObjectPath(Path) {}
	explicit FByVSoftObjectPath(FName Path)
		:SoftObjectPath(Path) {}
	explicit FByVSoftObjectPath(const WIDECHAR* Path)
		:SoftObjectPath(Path) {}
	explicit FByVSoftObjectPath(const ANSICHAR* Path)
		:SoftObjectPath(Path) {}
	explicit FByVSoftObjectPath(TYPE_OF_NULLPTR) {}
	
	/** Construct from an asset FName and subobject pair */
	FByVSoftObjectPath(FName InAssetPathName, FString InSubPathString)
		:SoftObjectPath(InAssetPathName, InSubPathString) {}
	
	/** Construct from an existing object in memory */
	FByVSoftObjectPath(const UObject* InObject)
		:SoftObjectPath(InObject) {}

	~FByVSoftObjectPath() {}

	
	FByVSoftObjectPath& operator=(const FByVSoftObjectPath& Path)	= default;
	FByVSoftObjectPath& operator=(FByVSoftObjectPath&& Path) = default;
	FByVSoftObjectPath& operator=(const FString& Path)						{ SetPath(FStringView(Path)); return *this; }
	FByVSoftObjectPath& operator=(FWideStringView Path)					{ SetPath(Path); return *this; }
	FByVSoftObjectPath& operator=(FAnsiStringView Path)					{ SetPath(Path); return *this; }
	FByVSoftObjectPath& operator=(FName Path)								{ SetPath(Path); return *this; }
	FByVSoftObjectPath& operator=(const WIDECHAR* Path)					{ SetPath(FWideStringView(Path)); return *this; }
	FByVSoftObjectPath& operator=(const ANSICHAR* Path)					{ SetPath(FAnsiStringView(Path)); return *this; }
	FByVSoftObjectPath& operator=(TYPE_OF_NULLPTR)							{ Reset(); return *this; }

	/** Returns string representation of reference, in form /package/path.assetname[:subpath] */
	FString ToString() const;

	/** Append string representation of reference, in form /package/path.assetname[:subpath] */
	void ToString(FStringBuilderBase& Builder) const;

	/** Returns the entire asset path as an FName, including both package and asset but not sub object */
	FORCEINLINE FName GetAssetPathName() const
	{
		return SoftObjectPath.GetAssetPathName();
	}

	/** Returns string version of asset path, including both package and asset but not sub object */
	FORCEINLINE FString GetAssetPathString() const
	{
		return SoftObjectPath.GetAssetPathString();
	}

	/** Returns the sub path, which is often empty */
	FORCEINLINE const FString& GetSubPathString() const
	{
		SoftObjectPath.GetSubPathString();
	}

	/** Returns /package/path, leaving off the asset name and sub object */
	FString GetLongPackageName() const
	{
		FString PackageName;
		GetAssetPathString().Split(TEXT("."), &PackageName, nullptr, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		return PackageName;
	}

	/** Returns assetname string, leaving off the /package/path part and sub object */
	FString GetAssetName() const
	{
		FString AssetName;
		GetAssetPathString().Split(TEXT("."), nullptr, &AssetName, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		return AssetName;
	}

	/** Sets asset path of this reference based on a string path */
	void SetPath(FWideStringView Path);
	void SetPath(FAnsiStringView Path);
	void SetPath(FName Path);
	void SetPath(const WIDECHAR* Path)			{ SetPath(FWideStringView(Path)); }
	void SetPath(const ANSICHAR* Path)			{ SetPath(FAnsiStringView(Path)); }
	void SetPath(const FString& Path)			{ SetPath(FStringView(Path)); }

	/**
	 * Attempts to load the asset, this will call LoadObject which can be very slow
	 * @param InLoadContext Optional load context when called from nested load callstack
	 * @return Loaded UObject, or nullptr if the reference is null or the asset fails to load
	 */
	UObject* TryLoad(FUObjectSerializeContext* InLoadContext = nullptr) const;

	/**
	 * Attempts to find a currently loaded object that matches this path
	 *
	 * @return Found UObject, or nullptr if not currently in memory
	 */
	UObject* ResolveObject() const;

	/** Resets reference to point to null */
	void Reset()
	{		
		SoftObjectPath.Reset();
	}
	
	/** Check if this could possibly refer to a real object, or was initialized to null */
	FORCEINLINE bool IsValid() const
	{
		return SoftObjectPath.IsValid();
	}

	/** Checks to see if this is initialized to null */
	FORCEINLINE bool IsNull() const
	{
		return SoftObjectPath.IsNull();
	}

	/** Check if this represents an asset, meaning it is not null but does not have a sub path */
	FORCEINLINE bool IsAsset() const
	{
		return SoftObjectPath.IsAsset();
	}

	/** Check if this represents a sub object, meaning it has a sub path */
	FORCEINLINE bool IsSubobject() const
	{
		return SoftObjectPath.IsSubobject();
	}

	/** Struct overrides */
	bool Serialize(FArchive& Ar);
	bool Serialize(FStructuredArchive::FSlot Slot);
	bool operator==(FByVSoftObjectPath const& Other) const;
	bool operator!=(FByVSoftObjectPath const& Other) const
	{
		return !(*this == Other);
	}

	bool ExportTextItem(FString& ValueStr, FByVSoftObjectPath const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;
	bool ImportTextItem( const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText, FArchive* InSerializingArchive = nullptr );
	bool SerializeFromMismatchedTag(struct FPropertyTag const& Tag, FStructuredArchive::FSlot Slot);

	/** Serializes the internal path and also handles save/PIE fixups. Call this from the archiver overrides */
	void SerializePath(FArchive& Ar);

	/** Fixes up path for saving, call if saving with a method that skips SerializePath. This can modify the path, it will return true if it was modified */
	bool PreSavePath(bool* bReportSoftObjectPathRedirects = nullptr);

	/** 
	 * Handles when a path has been loaded, call if loading with a method that skips SerializePath. This does not modify path but might call callbacks
	 * @param InArchive The archive that loaded this path
	 */
	void PostLoadPath(FArchive* InArchive) const;

	/** Fixes up this SoftObjectPath to add the PIE prefix depending on what is currently active, returns true if it was modified. The overload that takes an explicit PIE instance is preferred, if it's available. */
	bool FixupForPIE();

	/** Fixes up this SoftObjectPath to add the PIE prefix for the given PIEInstance index, returns true if it was modified */
	bool FixupForPIE(int32 PIEInstance);

	/** Fixes soft object path for CoreRedirects to handle renamed native objects, returns true if it was modified */
	bool FixupCoreRedirects();

	FORCEINLINE friend uint32 GetTypeHash(FByVSoftObjectPath const& This)
	{
		return GetTypeHash(This.SoftObjectPath);
	}

	/** Code needed by FSoftObjectPtr internals */
	static int32 GetCurrentTag()
	{
		return FSoftObjectPath::GetCurrentTag();
	}
	static int32 InvalidateTag()
	{
		return FSoftObjectPath::GetCurrentTag();
	}
	static FByVSoftObjectPath GetOrCreateIDForObject(const UObject* Object);
	
	/** Adds list of packages names that have been created specifically for PIE, this is used for editor fixup */
	static void AddPIEPackageName(FName NewPIEPackageName);
	
	/** Disables special PIE path handling, call when PIE finishes to clear list */
	static void ClearPIEPackageNames();
	
private:
	FSoftObjectPath SoftObjectPath;
};

inline FArchive& operator<<(FArchive& Ar, struct FByVSoftObjectPath& Value)
{
	Value.SerializePath(Ar);
	return Ar;
}