// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGFXPRIMDECK2D_H
#define	MOAIGFXPRIMDECK2D_H

#include <moai-sim/MOAIStandardDeck.h>
#include <moai-sim/MOAITransform.h>

//================================================================//
// ZLVertex
//================================================================//
class ZLVertex {
private:

	friend class MOAIGfxPrimDeck2D;

	ZLVec2D		mVtx;
	ZLVec2D		mUV;
};

//================================================================//
// ZLIndexedPrim
//================================================================//
class ZLIndexedPrim {
private:

	friend class MOAIGfxPrimDeck2D;

	u32		mVtxBase;
	u32		mVtxCount;

	u32		mIdxBase;
	u32		mIdxCount;
};

//================================================================//
// MOAIGfxPrimDeck2D
//================================================================//
/**	@lua	MOAIGfxPrimDeck2D
	@text	
*/
class MOAIGfxPrimDeck2D :
	public MOAIStandardDeck {
private:
	
	ZLLeanArray < ZLVertex >			mVertices;
	ZLLeanArray < u32 >					mIndices;
	ZLLeanArray	< ZLIndexedPrim >		mBatches;
	
	//----------------------------------------------------------------//
	static int	_exportGeometry			( lua_State* L );
	static int	_reserveIndices			( lua_State* L );
	static int	_reservePrims			( lua_State* L );
	static int	_reserveVertices		( lua_State* L );
	static int	_setIndex				( lua_State* L );
	static int	_setPrim				( lua_State* L );
	static int	_setVertex				( lua_State* L );

	//----------------------------------------------------------------//
	ZLBox			ComputeMaxBounds		();
	ZLBox			GetItemBounds			( u32 idx );

public:
	
	DECL_LUA_FACTORY ( MOAIGfxPrimDeck2D )
	
	//----------------------------------------------------------------//
	bool			Contains				( u32 idx, const ZLVec2D& vec );
	void			DrawIndex				( u32 idx, MOAIMaterialBatch& materials, ZLVec3D offset, ZLVec3D scale );
	u32				ExportGeometry			( u32 idx, MOAIVertexFormat& format, MOAIStream& vtxBuffer, MOAIStream& idxBuffer, u32 idxSize, MOAITransform* transform );
	bool			Inside					( u32 idx, MOAIMaterialBatch& materials, u32 granularity, ZLVec3D vec, float pad );
					MOAIGfxPrimDeck2D	();
					~MOAIGfxPrimDeck2D	();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			ReserveIndices			( u32 total );
	void			ReservePrims			( u32 total );
	void			ReserveVertices			( u32 total );
	void			SetIndex				( u32 idx, u32 index );
	void			SetPrim					( u32 idx, u32 vtxBase, u32 vtxCount, u32 idxBase, u32 idxCount );
	void			SetVertex				( u32 idx, ZLVertex& vtx );
};

#endif
