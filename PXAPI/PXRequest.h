//
//  PXRequest.h
//  PXAPI
//
//  Created by Ash Furrow on 2012-08-10.
//  Copyright (c) 2012 500px. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PXAPIHelper.h"

extern NSString *const PXRequestErrorConnectionDomain;
extern NSString *const PXRequestErrorRequestDomain;
extern NSString *const PXRequestAPIDomain;

extern NSString *const PXRequestPhotosCompleted;
extern NSString *const PXRequestPhotosFailed;

extern NSString *const PXRequestPhotoDetailsCompleted;
extern NSString *const PXRequestPhotoDetailsFailed;

extern NSString *const PXRequestLoggedInUserCompleted;
extern NSString *const PXRequestLoggedInUserFailed;

extern NSString *const PXRequestUserDetailsCompleted;
extern NSString *const PXRequestUserDetailsFailed;

extern NSString *const PXRequestToFavouritePhotoCompleted;
extern NSString *const PXRequestToFavouritePhotoFailed;

extern NSString *const PXRequestToVoteForPhotoCompleted;
extern NSString *const PXRequestToVoteForPhotoFailed;

extern NSString *const PXRequestToCommentOnPhotoCompleted;
extern NSString *const PXRequestToCommentOnPhotoFailed;

extern NSString *const PXRequestSearchCompleted;
extern NSString *const PXRequestSearchFailed;

extern NSString *const PXRequestToFollowUserCompleted;
extern NSString *const PXRequestToFollowUserFailed;

extern NSString *const PXRequestForUserFollowingListCompleted;
extern NSString *const PXRequestForUserFollowingListFailed;

extern NSString *const PXRequestForUserFollowersListCompleted;
extern NSString *const PXRequestForUserFollowersListFailed;

typedef enum : NSInteger
{
    PXRequestErrorCodeNoConsumerKeyAndSecret = 0,
    PXRequestErrorCodeUserNotLoggedIn,
    PXRequestErrorCodeCancelled,
}PXRequestErrorCode;

typedef enum : NSInteger
{
    //General API Errors
    PXRequestAPIDomainCodeRequiredParametersWereMissing = 0,
    PXRequestAPIDomainCodeRequiredParametersWereMissingOrInvalid,
    //User Errors
    PXRequestAPIDomainCodeUserHasBeenDisabled,
    PXRequestAPIDomainCodeUserDoesNotExist,
    PXRequestAPIDomainCodeUserHasBeenDisabledOrIsAlreadyFollowingUser,
    PXRequestAPIDomainCodeUserHasBeenDisabledOrIsNotFollowingUser,
    //Photo Errors
    PXRequestAPIDomainCodePhotoDoesNotExist,
    PXRequestAPIDomainCodePhotoWasDeletedOrUserWasDeactivated,
    PXRequestAPIDomainCodeCommentWasMissing,
    PXRequestAPIDomainCodeVoteWasRejected,      //common reasons are: current user is inactive, has not completed their profile, is trying to vote on their own photo, or has already voted for the photo.
    PXRequestAPIDomainCodeFavouriteWasRejected  //common reasons are: current user is inactive, has not completed their profile, or already has the photo in favorites list (or is not, and is trying to be removed).
}PXRequestAPIDomainCode;

extern NSString * const PXAuthenticationChangedNotification;
extern NSString * const PXAuthenticationFailedNotification;

typedef void (^PXRequestCompletionBlock)(NSDictionary *results, NSError *error);

typedef enum : NSInteger
{
    PXRequestStatusNotStarted = 0,
    PXRequestStatusStarted,
    PXRequestStatusCompleted,
    PXRequestStatusFailed,
    PXRequestStatusCancelled
}PXRequestStatus;

@interface PXRequest : NSObject

@property (nonatomic, readonly) NSURLRequest *urlRequest;
@property (nonatomic, readonly) PXRequestStatus requestStatus;

+(void)setConsumerKey:(NSString *)consumerKey consumerSecret:(NSString *)consumerSecret;
+(void)authenticateWithUserName:(NSString *)userName password:(NSString *)password;
+(void)removeUserAuthentication;
+(void)setAuthToken:(NSString *)authToken authSecret:(NSString *)authSecret;

-(void)cancel;

#pragma mark - Convenience methods for access 500px API

#pragma mark Photo Streams

+(PXRequest *)requestForPhotosWithCompletion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoFeature:(PXAPIHelperPhotoFeature)photoFeature completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoFeature:(PXAPIHelperPhotoFeature)photoFeature resultsPerPage:(NSInteger)resultsPerPage completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoFeature:(PXAPIHelperPhotoFeature)photoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoFeature:(PXAPIHelperPhotoFeature)photoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoFeature:(PXAPIHelperPhotoFeature)photoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoFeature:(PXAPIHelperPhotoFeature)photoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder except:(PXPhotoModelCategory)excludedCategory completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoFeature:(PXAPIHelperPhotoFeature)photoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder except:(PXPhotoModelCategory)excludedCategory only:(PXPhotoModelCategory)includedCategory completion:(PXRequestCompletionBlock)completionBlock;

#pragma mark Specific Users

+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder except:(PXPhotoModelCategory)excludedCategory completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserID:(NSInteger)userID userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder except:(PXPhotoModelCategory)excludedCategory only:(PXPhotoModelCategory)includedCategory completion:(PXRequestCompletionBlock)completionBlock;

+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder except:(PXPhotoModelCategory)excludedCategory completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotosOfUserName:(NSString *)userName userFeature:(PXAPIHelperUserPhotoFeature)userPhotoFeature resultsPerPage:(NSInteger)resultsPerPage page:(NSInteger)page photoSizes:(PXPhotoModelSize)photoSizesMask sortOrder:(PXAPIHelperSortOrder)sortOrder except:(PXPhotoModelCategory)excludedCategory only:(PXPhotoModelCategory)includedCategory completion:(PXRequestCompletionBlock)completionBlock;

#pragma mark Favourite, Vote, and Comment

//Requires Authentication
+(PXRequest *)requestToFavouritePhoto:(NSInteger)photoID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestToUnFavouritePhoto:(NSInteger)photoID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestToVoteForPhoto:(NSInteger)photoID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestToComment:(NSString *)comment onPhoto:(NSInteger)photoID completion:(PXRequestCompletionBlock)completionBlock;

#pragma mark Photo Details

//Comment pages are 1-indexed
//20 comments per page

+(PXRequest *)requestForPhotoID:(NSInteger)photoID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoID:(NSInteger)photoID commentsPage:(NSInteger)commentsPage completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForPhotoID:(NSInteger)photoID photoSizes:(PXPhotoModelSize)photoSizesMask commentsPage:(NSInteger)commentPage completion:(PXRequestCompletionBlock)completionBlock;

#pragma mark Photo Searching

//Search page results are 1-indexed

+(PXRequest *)requestForSearchTerm:(NSString *)searchTerm completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTerm:(NSString *)searchTerm page:(NSUInteger)page completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTerm:(NSString *)searchTerm page:(NSUInteger)page resultsPerPage:(NSUInteger)resultsPerPage completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTerm:(NSString *)searchTerm page:(NSUInteger)page resultsPerPage:(NSUInteger)resultsPerPage photoSizes:(PXPhotoModelSize)photoSizesMask completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTerm:(NSString *)searchTerm page:(NSUInteger)page resultsPerPage:(NSUInteger)resultsPerPage photoSizes:(PXPhotoModelSize)photoSizesMask except:(PXPhotoModelCategory)excludedCategory completion:(PXRequestCompletionBlock)completionBlock;

+(PXRequest *)requestForSearchTag:(NSString *)searchTag completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTag:(NSString *)searchTag page:(NSUInteger)page completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTag:(NSString *)searchTag page:(NSUInteger)page resultsPerPage:(NSUInteger)resultsPerPage completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTag:(NSString *)searchTag page:(NSUInteger)page resultsPerPage:(NSUInteger)resultsPerPage photoSizes:(PXPhotoModelSize)photoSizesMask completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForSearchTag:(NSString *)searchTag page:(NSUInteger)page resultsPerPage:(NSUInteger)resultsPerPage photoSizes:(PXPhotoModelSize)photoSizesMask except:(PXPhotoModelCategory)excludedCategory completion:(PXRequestCompletionBlock)completionBlock;

#pragma mark Users

//Requires Authentication
+(PXRequest *)requestForCurrentlyLoggedInUserWithCompletion:(PXRequestCompletionBlock)completionBlock;

+(PXRequest *)requestForUserWithID:(NSInteger)userID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForUserWithUserName:(NSString *)userName completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForUserWithEmailAddress:(NSString *)userEmailAddress completion:(PXRequestCompletionBlock)completionBlock;

+(PXRequest *)requestForUserSearchWithTerm:(NSString *)searchTerm completion:(PXRequestCompletionBlock)completionBlock;

//pages are 1-indexed
+(PXRequest *)requestForUserFollowing:(NSInteger)userID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForUserFollowing:(NSInteger)userID page:(NSInteger)page completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForUserFollowers:(NSInteger)userID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestForUserFollowers:(NSInteger)userID page:(NSInteger)page completion:(PXRequestCompletionBlock)completionBlock;

//Requires Authentication
+(PXRequest *)requestToFollowUser:(NSInteger)userToFollowID completion:(PXRequestCompletionBlock)completionBlock;
+(PXRequest *)requestToUnFollowUser:(NSInteger)userToUnFollowID completion:(PXRequestCompletionBlock)completionBlock;


@end
