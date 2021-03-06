//
//  ofxFBXMesh.h
//  ofxFBX-Example-Importer
//
//  Created by Nick Hardeman on 10/31/13.
//
//


#pragma once

#define FBXSDK_NEW_API

#include "ofMain.h"

/*
#if defined(TARGET_OSX)
    #include "fbxsdk.h"
#endif

#if defined(TARGET_LINUX) 
    #include <fbxsdk.h>
	#include <fbxscene.h>
#else
	#include "fbxsdk.h"
	#include "fbxsdk/scene/fbxscene.h"
#endif
	*/

#include <fbxsdk.h>

/*
#if defined(TARGET_LINUX) 
    #include <fbxsdk.h>
#else
	#include "fbxsdk.h"
#endif
*/

//#include <fbxsdk/scene/fbxscene.h>

#include "ofxFBXUtils.h"
#include "ofxFBXAnimation.h"
#include "ofxFBXMesh.h"
#include "ofxFBXBone.h"
#include "ofxFBXMeshMaterial.h"
#include "ofxFBXCluster.h"
#include "ofxFBXSkeleton.h"
#include "ofxFBXPose.h"
#include "ofxFBXCachedSkeletonAnimation.h"

class ofxFBXSceneSettings {
public:
    ofxFBXSceneSettings() {
        importMaterials                 = true;
        importTextures                  = true;
        importBones                     = true; // bones /
        importShapes                    = true;
        importGobos                     = true;
        importAnimations                = true;
        cacheSkeletonAnimations         = false; // currently can cause problems //
    }
    
    bool importBones;
    bool importMaterials;
    bool importTextures;
    bool importShapes;
    bool importGobos;
    bool importAnimations;
    bool cacheSkeletonAnimations;
};


class ofxFBXScene{
public:
    
    ofxFBXScene();
    ~ofxFBXScene();
    
	bool load( string path, ofxFBXSceneSettings aSettings = ofxFBXSceneSettings() );
    
    FbxScene* getFBXScene();
    
	vector< shared_ptr<ofxFBXMesh> >& getMeshes();
//    vector< shared_ptr<ofxFBXSkeleton> >& getSkeletons();
    
    
    int getNumAnimations();
    bool areAnimationsEnabled();
    void populateAnimations( vector<ofxFBXAnimation>& aInVector );
    void populateCachedSkeletonAnimations( vector< vector<ofxFBXCachedSkeletonAnimation> >& aInVector );
    
    void populateSkeletons( vector< shared_ptr<ofxFBXSkeleton> >& aInSkeletons );
    
    int getNumPoses();
    void populatePoses( vector< shared_ptr<ofxFBXPose> >& aInPoses );
    
    string getFbxFilePath();
    string getFbxFolderPath();

private:
    void cacheTexturesInScene( FbxScene* pScene );
    void deleteCachedTexturesInScene( FbxScene* pScene );
    bool isValidTexturePath( string aPathToTexture );
    
    void cacheMaterialsRecursive( FbxNode* pNode );
    void deleteCachedMaterialsRecursive( FbxNode* pNode );
    
    void populateAnimationInformation();
    void populateCachedSkeletonAnimationInformation();
    void populateMeshesRecursive( FbxNode* pNode, FbxAnimLayer* pAnimLayer );
    void populateBonesRecursive( FbxNode* pNode, FbxAnimLayer* pAnimLayer );
    void parentBonesRecursive( FbxNode* pNode, list<FbxNode*>& aSkeletonBases );
    void constructSkeletons( FbxNode* pNode, FbxAnimLayer* pAnimLayer );
    void constructSkeletonsRecursive( ofxFBXSkeleton* aSkeleton, FbxNode* pNode );
    
    FbxTime fbxFrameTime;
    string fbxFilePath;
    
    vector< shared_ptr<ofxFBXBone> > bones;
    vector< shared_ptr<ofxFBXCluster> > clusters;
    
    vector< shared_ptr<ofxFBXMesh> > meshes;
    vector< shared_ptr<ofxFBXSkeleton> > skeletons;
	
    FbxManager* lSdkManager;
	FbxScene* lScene;
    
    vector<ofxFBXAnimation> animations;
    FbxAnimLayer* currentFbxAnimationLayer;
    
    vector< vector<ofxFBXCachedSkeletonAnimation> > cachedSkeletonAnimations;
    
    ofxFBXSceneSettings _settings;
};















