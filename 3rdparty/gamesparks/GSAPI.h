
#import "GSData.h"

#ifndef GameSparks_IOS_GSAPI_h
#define GameSparks_IOS_GSAPI_h

@interface GSBulkJob : GSData
-(NSNumber*) getActualCount;
-(NSDate*) getCompleted;
-(NSDate*) getCreated;
-(NSDictionary*) getData;
-(NSNumber*) getDoneCount;
-(NSNumber*) getErrorCount;
-(NSNumber*) getEstimatedCount;
-(NSString*) getId;
-(NSString*) getModuleShortCode;
-(NSDictionary*) getPlayerQuery;
-(NSDate*) getScheduledTime;
-(NSString*) getScript;
-(NSDate*) getStarted;
-(NSString*) getState;
@end
@interface GSInvitableFriend : GSData
-(NSString*) getDisplayName;
-(NSString*) getId;
-(NSString*) getProfilePic;
@end
@interface GSAchievement : GSData
-(NSString*) getDescription;
-(BOOL) getEarned;
-(NSString*) getName;
-(NSDictionary*) getPropertySet;
-(NSString*) getShortCode;
@end
@interface GSBundledGood : GSData
-(NSNumber*) getQty;
-(NSString*) getShortCode;
@end
@interface GSVirtualGood : GSData
-(NSString*) getWP8StoreProductId;
-(NSString*) getAmazonStoreProductId;
-(NSNumber*) getBaseCurrency1Cost;
-(NSNumber*) getBaseCurrency2Cost;
-(NSNumber*) getBaseCurrency3Cost;
-(NSNumber*) getBaseCurrency4Cost;
-(NSNumber*) getBaseCurrency5Cost;
-(NSNumber*) getBaseCurrency6Cost;
-(NSDictionary*) getBaseCurrencyCosts;
-(NSArray*) getBundledGoods;
-(NSNumber*) getCurrency1Cost;
-(NSNumber*) getCurrency2Cost;
-(NSNumber*) getCurrency3Cost;
-(NSNumber*) getCurrency4Cost;
-(NSNumber*) getCurrency5Cost;
-(NSNumber*) getCurrency6Cost;
-(NSDictionary*) getCurrencyCosts;
-(NSString*) getDescription;
-(BOOL) getDisabled;
-(NSString*) getGooglePlayProductId;
-(NSString*) getIosAppStoreProductId;
-(NSNumber*) getMaxQuantity;
-(NSString*) getName;
-(NSDictionary*) getPropertySet;
-(NSString*) getPsnStoreProductId;
-(NSNumber*) getSegmentedCurrency1Cost;
-(NSNumber*) getSegmentedCurrency2Cost;
-(NSNumber*) getSegmentedCurrency3Cost;
-(NSNumber*) getSegmentedCurrency4Cost;
-(NSNumber*) getSegmentedCurrency5Cost;
-(NSNumber*) getSegmentedCurrency6Cost;
-(NSDictionary*) getSegmentedCurrencyCosts;
-(NSString*) getShortCode;
-(NSString*) getSteamStoreProductId;
-(NSString*) getTags;
-(NSString*) getType;
-(NSString*) getW8StoreProductId;
@end
@interface GSPlayer : GSData
		
-(NSString*) getAchievements;
-(NSString*) getDisplayName;
-(NSDictionary*) getExternalIds;
-(NSString*) getId;
-(BOOL) getOnline;
-(NSDictionary*) getScriptData;
		
-(NSString*) getVirtualGoods;
@end
@interface GSTeam : GSData
-(NSArray*) getMembers;
-(GSPlayer*) getOwner;
-(NSString*) getTeamId;
-(NSString*) getTeamName;
-(NSString*) getTeamType;
@end
@interface GSLeaderboard : GSData
-(NSString*) getDescription;
-(NSString*) getName;
-(NSDictionary*) getPropertySet;
-(NSString*) getShortCode;
@end
@interface GSChatMessage : GSData
-(NSString*) getFromId;
-(NSString*) getId;
-(NSString*) getMessage;
-(NSDate*) getWhen;
-(NSString*) getWho;
@end
@interface GSPlayerDetail : GSData
-(NSDictionary*) getExternalIds;
-(NSString*) getId;
-(NSString*) getName;
@end
@interface GSUploadData : GSData
-(NSString*) getFileName;
-(NSString*) getPlayerId;
@end
@interface GSChallengeType : GSData
-(NSString*) getChallengeShortCode;
-(NSString*) getDescription;
-(NSString*) getGetleaderboardName;
-(NSString*) getName;
-(NSString*) getTags;
@end
@interface GSBoughtitem : GSData
-(NSNumber*) getQuantity;
-(NSString*) getShortCode;
@end
@interface GSPlayerMessage : GSData
-(NSString*) getId;
-(NSDictionary*) getMessage;
-(BOOL) getSeen;
-(NSString*) getStatus;
-(NSDate*) getWhen;
@end
@interface GSMatchedPlayer : GSData
-(NSDictionary*) getLocation;
-(NSDictionary*) getParticipantData;
-(NSString*) getPlayerId;
-(NSNumber*) getSkill;
@end
@interface GSPendingMatch : GSData
-(NSString*) getId;
-(NSDictionary*) getMatchData;
-(NSString*) getMatchGroup;
-(NSString*) getMatchShortCode;
-(NSArray*) getMatchedPlayers;
-(NSNumber*) getSkill;
@end
@interface GSParticipant : GSData
		
-(NSString*) getAchievements;
-(NSString*) getDisplayName;
-(NSDictionary*) getExternalIds;
-(NSString*) getId;
-(BOOL) getOnline;
-(NSDictionary*) getParticipantData;
-(NSNumber*) getPeerId;
-(NSDictionary*) getScriptData;
		
-(NSString*) getVirtualGoods;
@end
@interface GSPlayerTransactionItem : GSData
-(NSNumber*) getAmount;
-(NSNumber*) getNewValue;
-(NSString*) getType;
@end
@interface GSPlayerTransaction : GSData
-(NSArray*) getItems;
-(NSString*) getOriginalRequestId;
-(NSString*) getPlayerId;
-(NSString*) getReason;
-(NSDate*) getRevokeDate;
-(BOOL) getRevoked;
-(NSString*) getScript;
-(NSString*) getScriptType;
-(NSString*) getTransactionId;
-(NSDate*) getWhen;
@end
@interface GSPlayerTurnCount : GSData
-(NSString*) getCount;
-(NSString*) getPlayerId;
@end
@interface GSChallenge : GSData
-(NSArray*) getAccepted;
-(NSString*) getChallengeId;
-(NSString*) getChallengeMessage;
-(NSString*) getChallengeName;
-(NSArray*) getChallenged;
-(GSPlayerDetail*) getChallenger;
-(NSNumber*) getCurrency1Wager;
-(NSNumber*) getCurrency2Wager;
-(NSNumber*) getCurrency3Wager;
-(NSNumber*) getCurrency4Wager;
-(NSNumber*) getCurrency5Wager;
-(NSNumber*) getCurrency6Wager;
-(NSDictionary*) getCurrencyWagers;
-(NSArray*) getDeclined;
-(NSDate*) getEndDate;
-(NSDate*) getExpiryDate;
-(NSNumber*) getMaxTurns;
-(NSString*) getNextPlayer;
-(NSDictionary*) getScriptData;
-(NSString*) getShortCode;
-(NSDate*) getStartDate;
-(NSString*) getState;
-(NSArray*) getTurnCount;
@end
@interface GSLeaderboardData : GSData
-(NSString*) getCity;
-(NSString*) getCountry;
-(NSDictionary*) getExternalIds;
-(NSNumber*) getRank;
-(NSString*) getUserId;
-(NSString*) getUserName;
-(NSString*) getWhen;
-(NSNumber*)getNumberValue:(NSString*)shortCode;
-(NSString*)getStringValue:(NSString*)shortCode;
@end
@interface GSLeaderboardRankDetails : GSData
-(NSArray*) getFriendsPassed;
-(NSNumber*) getGlobalCount;
-(NSNumber*) getGlobalFrom;
-(NSNumber*) getGlobalFromPercent;
-(NSNumber*) getGlobalTo;
-(NSNumber*) getGlobalToPercent;
-(NSNumber*) getSocialCount;
-(NSNumber*) getSocialFrom;
-(NSNumber*) getSocialFromPercent;
-(NSNumber*) getSocialTo;
-(NSNumber*) getSocialToPercent;
-(NSArray*) getTopNPassed;
@end
@interface GSSocialStatus : GSData
-(BOOL) getActive;
-(NSDate*) getExpires;
-(NSString*) getSystemId;
@end
@interface GSLocation : GSData
-(NSString*) getCity;
-(NSString*) getCountry;
-(NSNumber*) getLatitide;
-(NSNumber*) getLongditute;
@end

@interface GSAcceptChallengeResponse : GSResponse
-(NSString*) getChallengeInstanceId;
@end
@interface GSAccountDetailsResponse : GSResponse
		
-(NSString*) getAchievements;
-(NSDictionary*) getCurrencies;
-(NSNumber*) getCurrency1;
-(NSNumber*) getCurrency2;
-(NSNumber*) getCurrency3;
-(NSNumber*) getCurrency4;
-(NSNumber*) getCurrency5;
-(NSNumber*) getCurrency6;
-(NSString*) getDisplayName;
-(NSDictionary*) getExternalIds;
-(GSLocation*) getLocation;
-(NSDictionary*) getReservedCurrencies;
-(NSDictionary*) getReservedCurrency1;
-(NSDictionary*) getReservedCurrency2;
-(NSDictionary*) getReservedCurrency3;
-(NSDictionary*) getReservedCurrency4;
-(NSDictionary*) getReservedCurrency5;
-(NSDictionary*) getReservedCurrency6;
-(NSString*) getUserId;
-(NSDictionary*) getVirtualGoods;
@end
@interface GSAnalyticsResponse : GSResponse
@end
@interface GSAroundMeLeaderboardResponse : GSResponse
-(NSString*) getChallengeInstanceId;
-(NSArray*) getData;
-(NSArray*) getFirst;
-(NSArray*) getLast;
-(NSString*) getLeaderboardShortCode;
-(BOOL) getSocial;
@end
@interface GSAuthenticationResponse : GSResponse
-(NSString*) getAuthToken;
-(NSString*) getDisplayName;
-(BOOL) getNewPlayer;
-(GSPlayer*) getSwitchSummary;
-(NSString*) getUserId;
@end
@interface GSBatchAdminResponse : GSResponse
-(NSDictionary*) getResponses;
@end
@interface GSBuyVirtualGoodResponse : GSResponse
-(NSArray*) getBoughtItems;
-(NSDictionary*) getCurrenciesAdded;
-(NSNumber*) getCurrency1Added;
-(NSNumber*) getCurrency2Added;
-(NSNumber*) getCurrency3Added;
-(NSNumber*) getCurrency4Added;
-(NSNumber*) getCurrency5Added;
-(NSNumber*) getCurrency6Added;
-(NSNumber*) getCurrencyConsumed;
-(NSString*) getCurrencyShortCode;
-(NSNumber*) getCurrencyType;
		
-(NSString*) getInvalidItems;
		
-(NSString*) getTransactionIds;
@end
@interface GSCancelBulkJobAdminResponse : GSResponse
-(NSArray*) getBulkJobs;
@end
@interface GSChangeUserDetailsResponse : GSResponse
@end
@interface GSChatOnChallengeResponse : GSResponse
-(NSString*) getChallengeInstanceId;
@end
@interface GSConsumeVirtualGoodResponse : GSResponse
@end
@interface GSCreateChallengeResponse : GSResponse
-(NSString*) getChallengeInstanceId;
@end
@interface GSCreateTeamResponse : GSResponse
-(NSArray*) getMembers;
-(GSPlayer*) getOwner;
-(NSString*) getTeamId;
-(NSString*) getTeamName;
-(NSString*) getTeamType;
@end
@interface GSDeclineChallengeResponse : GSResponse
-(NSString*) getChallengeInstanceId;
@end
@interface GSDismissMessageResponse : GSResponse
@end
@interface GSDismissMultipleMessagesResponse : GSResponse
		
-(NSString*) getFailedDismissals;
-(NSNumber*) getMessagesDismissed;
@end
@interface GSDropTeamResponse : GSResponse
@end
@interface GSEndSessionResponse : GSResponse
-(NSNumber*) getSessionDuration;
@end
@interface GSFindChallengeResponse : GSResponse
-(NSArray*) getChallengeInstances;
@end
@interface GSFindMatchResponse : GSResponse
-(NSString*) getAccessToken;
-(NSString*) getHost;
-(NSDictionary*) getMatchData;
-(NSString*) getMatchId;
-(NSArray*) getOpponents;
-(NSNumber*) getPeerId;
-(NSString*) getPlayerId;
-(NSNumber*) getPort;
@end
@interface GSFindPendingMatchesResponse : GSResponse
-(NSArray*) getPendingMatches;
@end
@interface GSGameSparksErrorResponse : GSResponse
@end
@interface GSGetChallengeResponse : GSResponse
-(GSChallenge*) getChallenge;
@end
@interface GSGetDownloadableResponse : GSResponse
-(NSDate*) getLastModified;
-(NSString*) getShortCode;
-(NSNumber*) getSize;
-(NSString*) getUrl;
@end
@interface GSGetLeaderboardEntriesResponse : GSResponse
-(NSDictionary*) getResults;
-(GSLeaderboardData*)getEntryForLeaderboard:(NSString*)shortCode;
@end
@interface GSGetMessageResponse : GSResponse
-(NSDictionary*) getMessage;
-(NSString*) getStatus;
@end
@interface GSGetMyTeamsResponse : GSResponse
-(NSArray*) getTeams;
@end
@interface GSGetPropertyResponse : GSResponse
-(NSDictionary*) getProperty;
@end
@interface GSGetPropertySetResponse : GSResponse
-(NSDictionary*) getPropertySet;
@end
@interface GSGetTeamResponse : GSResponse
-(NSArray*) getMembers;
-(GSPlayer*) getOwner;
-(NSString*) getTeamId;
-(NSString*) getTeamName;
-(NSString*) getTeamType;
-(NSArray*) getTeams;
@end
@interface GSGetUploadUrlResponse : GSResponse
-(NSString*) getUrl;
@end
@interface GSGetUploadedResponse : GSResponse
-(NSNumber*) getSize;
-(NSString*) getUrl;
@end
@interface GSJoinChallengeResponse : GSResponse
-(BOOL) getJoined;
@end
@interface GSJoinPendingMatchResponse : GSResponse
-(GSPendingMatch*) getPendingMatch;
@end
@interface GSJoinTeamResponse : GSResponse
-(NSArray*) getMembers;
-(GSPlayer*) getOwner;
-(NSString*) getTeamId;
-(NSString*) getTeamName;
-(NSString*) getTeamType;
@end
@interface GSLeaderboardDataResponse : GSResponse
-(NSString*) getChallengeInstanceId;
-(NSArray*) getData;
-(NSArray*) getFirst;
-(NSArray*) getLast;
-(NSString*) getLeaderboardShortCode;
@end
@interface GSLeaderboardsEntriesResponse : GSResponse
-(NSDictionary*) getResults;
@end
@interface GSLeaveTeamResponse : GSResponse
-(NSArray*) getMembers;
-(GSPlayer*) getOwner;
-(NSString*) getTeamId;
-(NSString*) getTeamName;
-(NSString*) getTeamType;
@end
@interface GSListAchievementsResponse : GSResponse
-(NSArray*) getAchievements;
@end
@interface GSListBulkJobsAdminResponse : GSResponse
-(NSArray*) getBulkJobs;
@end
@interface GSListChallengeResponse : GSResponse
-(NSArray*) getChallengeInstances;
@end
@interface GSListChallengeTypeResponse : GSResponse
-(NSArray*) getChallengeTemplates;
@end
@interface GSListGameFriendsResponse : GSResponse
-(NSArray*) getFriends;
@end
@interface GSListInviteFriendsResponse : GSResponse
-(NSArray*) getFriends;
@end
@interface GSListLeaderboardsResponse : GSResponse
-(NSArray*) getLeaderboards;
@end
@interface GSListMessageDetailResponse : GSResponse
-(NSArray*) getMessageList;
@end
@interface GSListMessageResponse : GSResponse
		
-(NSDictionary*) getMessageList;
@end
@interface GSListMessageSummaryResponse : GSResponse
		
-(NSDictionary*) getMessageList;
@end
@interface GSListTeamChatResponse : GSResponse
-(NSArray*) getMessages;
@end
@interface GSListTeamsResponse : GSResponse
-(NSArray*) getTeams;
@end
@interface GSListTransactionsResponse : GSResponse
-(NSArray*) getTransactionList;
@end
@interface GSListVirtualGoodsResponse : GSResponse
-(NSArray*) getVirtualGoods;
@end
@interface GSLogChallengeEventResponse : GSResponse
@end
@interface GSLogEventResponse : GSResponse
@end
@interface GSMatchDetailsResponse : GSResponse
-(NSString*) getAccessToken;
-(NSString*) getHost;
-(NSDictionary*) getMatchData;
-(NSString*) getMatchId;
-(NSArray*) getOpponents;
-(NSNumber*) getPeerId;
-(NSString*) getPlayerId;
-(NSNumber*) getPort;
@end
@interface GSMatchmakingResponse : GSResponse
@end
@interface GSPushRegistrationResponse : GSResponse
-(NSString*) getRegistrationId;
@end
@interface GSRegistrationResponse : GSResponse
-(NSString*) getAuthToken;
-(NSString*) getDisplayName;
-(BOOL) getNewPlayer;
-(GSPlayer*) getSwitchSummary;
-(NSString*) getUserId;
@end
@interface GSRevokePurchaseGoodsResponse : GSResponse
-(NSDictionary*) getRevokedGoods;
@end
@interface GSScheduleBulkJobAdminResponse : GSResponse
-(NSNumber*) getEstimatedCount;
-(NSString*) getJobId;
@end
@interface GSSendFriendMessageResponse : GSResponse
@end
@interface GSSendTeamChatMessageResponse : GSResponse
@end
@interface GSSocialDisconnectResponse : GSResponse
@end
@interface GSSocialStatusResponse : GSResponse
-(NSArray*) getStatuses;
@end
@interface GSUpdateMessageResponse : GSResponse
@end
@interface GSWithdrawChallengeResponse : GSResponse
-(NSString*) getChallengeInstanceId;
@end

@interface GSAchievementEarnedMessage : GSMessage
-(NSString*) getAchievementName;
-(NSString*) getAchievementShortCode;
-(NSString*) getCurrency1Earned;
-(NSString*) getCurrency2Earned;
-(NSString*) getCurrency3Earned;
-(NSString*) getCurrency4Earned;
-(NSString*) getCurrency5Earned;
-(NSString*) getCurrency6Earned;
-(NSDictionary*) getCurrencyAwards;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getVirtualGoodEarned;
@end
@interface GSChallengeAcceptedMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeChangedMessage : GSMessage
-(GSChallenge*) getChallenge;
-(GSLeaderboardData*) getLeaderboardData;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeChatMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeDeclinedMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeDrawnMessage : GSMessage
-(GSChallenge*) getChallenge;
-(GSLeaderboardData*) getLeaderboardData;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSChallengeExpiredMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSChallengeIssuedMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeJoinedMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeLapsedMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSChallengeLostMessage : GSMessage
-(GSChallenge*) getChallenge;
-(GSLeaderboardData*) getLeaderboardData;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWinnerName;
@end
@interface GSChallengeStartedMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSChallengeTurnTakenMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeWaitingMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSChallengeWithdrawnMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSChallengeWonMessage : GSMessage
-(GSChallenge*) getChallenge;
-(NSNumber*) getCurrency1Won;
-(NSNumber*) getCurrency2Won;
-(NSNumber*) getCurrency3Won;
-(NSNumber*) getCurrency4Won;
-(NSNumber*) getCurrency5Won;
-(NSNumber*) getCurrency6Won;
-(NSDictionary*) getCurrencyWinnings;
-(GSLeaderboardData*) getLeaderboardData;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWinnerName;
@end
@interface GSFriendMessage : GSMessage
-(NSString*) getFromId;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSGlobalRankChangedMessage : GSMessage
-(NSNumber*) getGameId;
-(NSString*) getLeaderboardName;
-(NSString*) getLeaderboardShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(GSLeaderboardData*) getThem;
-(NSString*) getTitle;
-(GSLeaderboardData*) getYou;
@end
@interface GSMatchFoundMessage : GSMessage
-(NSString*) getAccessToken;
-(NSString*) getHost;
-(NSDictionary*) getMatchData;
-(NSString*) getMatchGroup;
-(NSString*) getMatchId;
-(NSString*) getMatchShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSArray*) getParticipants;
-(NSNumber*) getPort;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSMatchNotFoundMessage : GSMessage
-(NSDictionary*) getMatchData;
-(NSString*) getMatchGroup;
-(NSString*) getMatchShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSDictionary*) getParticipantData;
-(NSArray*) getParticipants;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSMatchUpdatedMessage : GSMessage
		
-(NSString*) getAddedPlayers;
-(NSDictionary*) getMatchData;
-(NSString*) getMatchGroup;
-(NSString*) getMatchId;
-(NSString*) getMatchShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSArray*) getParticipants;
		
-(NSString*) getRemovedPlayers;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSNewHighScoreMessage : GSMessage
-(GSLeaderboardData*) getLeaderboardData;
-(NSString*) getLeaderboardName;
-(NSString*) getLeaderboardShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(GSLeaderboardRankDetails*) getRankDetails;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSNewTeamScoreMessage : GSMessage
-(GSLeaderboardData*) getLeaderboardData;
-(NSString*) getLeaderboardName;
-(NSString*) getLeaderboardShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(GSLeaderboardRankDetails*) getRankDetails;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSScriptMessage : GSMessage
-(NSDictionary*) getData;
-(NSString*) getExtCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
@end
@interface GSSessionTerminatedMessage : GSMessage
-(NSString*) getAuthToken;
@end
@interface GSSocialRankChangedMessage : GSMessage
-(NSNumber*) getGameId;
-(NSString*) getLeaderboardName;
-(NSString*) getLeaderboardShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(GSLeaderboardData*) getThem;
-(NSString*) getTitle;
-(GSLeaderboardData*) getYou;
@end
@interface GSTeamChatMessage : GSMessage
-(NSString*) getChatMessageId;
-(NSString*) getFromId;
-(NSString*) getMessage;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getOwnerId;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTeamId;
-(NSString*) getTeamType;
-(NSString*) getTitle;
-(NSString*) getWho;
@end
@interface GSTeamRankChangedMessage : GSMessage
-(NSNumber*) getGameId;
-(NSString*) getLeaderboardName;
-(NSString*) getLeaderboardShortCode;
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(GSLeaderboardData*) getThem;
-(NSString*) getTitle;
-(GSLeaderboardData*) getYou;
@end
@interface GSUploadCompleteMessage : GSMessage
-(NSString*) getMessageId;
-(BOOL) getNotification;
-(NSString*) getSubTitle;
-(NSString*) getSummary;
-(NSString*) getTitle;
-(NSDictionary*) getUploadData;
-(NSString*) getUploadId;
@end


@interface GSAcceptChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSAcceptChallengeResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setMessage:(NSString*) message;
@end


@interface GSAccountDetailsRequest : GSRequest
-(void) setCallback:(void (^)(GSAccountDetailsResponse*))callback;
@end


@interface GSAmazonBuyGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*))callback;
-(void) setAmazonUserId:(NSString*) amazonUserId;
-(void) setCurrencyCode:(NSString*) currencyCode;
-(void) setReceiptId:(NSString*) receiptId;
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice;
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer;
@end


@interface GSAmazonConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSAnalyticsRequest : GSRequest
-(void) setCallback:(void (^)(GSAnalyticsResponse*))callback;
-(void) setData:(NSDictionary*) data;
-(void) setEnd:(BOOL) end;
-(void) setKey:(NSString*) key;
-(void) setStart:(BOOL) start;
@end


@interface GSAroundMeLeaderboardRequest : GSRequest
-(void) setCallback:(void (^)(GSAroundMeLeaderboardResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setCustomIdFilter:(NSDictionary*) customIdFilter;
-(void) setDontErrorOnNotSocial:(BOOL) dontErrorOnNotSocial;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setFriendIds:(NSArray*) friendIds;
-(void) setIncludeFirst:(NSNumber*) includeFirst;
-(void) setIncludeLast:(NSNumber*) includeLast;
-(void) setInverseSocial:(BOOL) inverseSocial;
-(void) setLeaderboardShortCode:(NSString*) leaderboardShortCode;
-(void) setSocial:(BOOL) social;
-(void) setTeamIds:(NSArray*) teamIds;
-(void) setTeamTypes:(NSArray*) teamTypes;
@end


@interface GSAuthenticationRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setPassword:(NSString*) password;
-(void) setUserName:(NSString*) userName;
@end


@interface GSBatchAdminRequest : GSRequest
-(void) setCallback:(void (^)(GSBatchAdminResponse*))callback;
-(void) setPlayerIds:(NSArray*) playerIds;
-(void) setRequest:(NSDictionary*) request;
@end


@interface GSBuyVirtualGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*))callback;
-(void) setCurrencyShortCode:(NSString*) currencyShortCode;
-(void) setCurrencyType:(NSNumber*) currencyType;
-(void) setQuantity:(NSNumber*) quantity;
-(void) setShortCode:(NSString*) shortCode;
@end


@interface GSCancelBulkJobAdminRequest : GSRequest
-(void) setCallback:(void (^)(GSCancelBulkJobAdminResponse*))callback;
-(void) setBulkJobIds:(NSArray*) bulkJobIds;
@end


@interface GSChangeUserDetailsRequest : GSRequest
-(void) setCallback:(void (^)(GSChangeUserDetailsResponse*))callback;
-(void) setDisplayName:(NSString*) displayName;
-(void) setLanguage:(NSString*) language;
-(void) setNewPassword:(NSString*) newPassword;
-(void) setOldPassword:(NSString*) oldPassword;
-(void) setUserName:(NSString*) userName;
@end


@interface GSChatOnChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSChatOnChallengeResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setMessage:(NSString*) message;
@end


@interface GSConsumeVirtualGoodRequest : GSRequest
-(void) setCallback:(void (^)(GSConsumeVirtualGoodResponse*))callback;
-(void) setQuantity:(NSNumber*) quantity;
-(void) setShortCode:(NSString*) shortCode;
@end


@interface GSCreateChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSCreateChallengeResponse*))callback;
-(void) setAccessType:(NSString*) accessType;
-(void) setAutoStartJoinedChallengeOnMaxPlayers:(BOOL) autoStartJoinedChallengeOnMaxPlayers;
-(void) setChallengeMessage:(NSString*) challengeMessage;
-(void) setChallengeShortCode:(NSString*) challengeShortCode;
-(void) setCurrency1Wager:(NSNumber*) currency1Wager;
-(void) setCurrency2Wager:(NSNumber*) currency2Wager;
-(void) setCurrency3Wager:(NSNumber*) currency3Wager;
-(void) setCurrency4Wager:(NSNumber*) currency4Wager;
-(void) setCurrency5Wager:(NSNumber*) currency5Wager;
-(void) setCurrency6Wager:(NSNumber*) currency6Wager;
-(void) setCurrencyWagers:(NSDictionary*) currencyWagers;
-(void) setEligibilityCriteria:(NSDictionary*) eligibilityCriteria;
-(void) setEndTime:(NSDate*) endTime;
-(void) setExpiryTime:(NSDate*) expiryTime;
-(void) setMaxAttempts:(NSNumber*) maxAttempts;
-(void) setMaxPlayers:(NSNumber*) maxPlayers;
-(void) setMinPlayers:(NSNumber*) minPlayers;
-(void) setSilent:(BOOL) silent;
-(void) setStartTime:(NSDate*) startTime;
-(void) setUsersToChallenge:(NSArray*) usersToChallenge;
@end


@interface GSCreateTeamRequest : GSRequest
-(void) setCallback:(void (^)(GSCreateTeamResponse*))callback;
-(void) setTeamId:(NSString*) teamId;
-(void) setTeamName:(NSString*) teamName;
-(void) setTeamType:(NSString*) teamType;
@end


@interface GSDeclineChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSDeclineChallengeResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setMessage:(NSString*) message;
@end


@interface GSDeviceAuthenticationRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setDeviceId:(NSString*) deviceId;
-(void) setDeviceModel:(NSString*) deviceModel;
-(void) setDeviceName:(NSString*) deviceName;
-(void) setDeviceOS:(NSString*) deviceOS;
-(void) setDeviceType:(NSString*) deviceType;
-(void) setDisplayName:(NSString*) displayName;
-(void) setOperatingSystem:(NSString*) operatingSystem;
-(void) setSegments:(NSDictionary*) segments;
@end


@interface GSDismissMessageRequest : GSRequest
-(void) setCallback:(void (^)(GSDismissMessageResponse*))callback;
-(void) setMessageId:(NSString*) messageId;
@end


@interface GSDismissMultipleMessagesRequest : GSRequest
-(void) setCallback:(void (^)(GSDismissMultipleMessagesResponse*))callback;
-(void) setMessageIds:(NSArray*) messageIds;
@end


@interface GSDropTeamRequest : GSRequest
-(void) setCallback:(void (^)(GSDropTeamResponse*))callback;
-(void) setOwnerId:(NSString*) ownerId;
-(void) setTeamId:(NSString*) teamId;
-(void) setTeamType:(NSString*) teamType;
@end


@interface GSEndSessionRequest : GSRequest
-(void) setCallback:(void (^)(GSEndSessionResponse*))callback;
@end


@interface GSFacebookConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setCode:(NSString*) code;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSFindChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSFindChallengeResponse*))callback;
-(void) setAccessType:(NSString*) accessType;
-(void) setCount:(NSNumber*) count;
-(void) setEligibility:(NSDictionary*) eligibility;
-(void) setOffset:(NSNumber*) offset;
-(void) setShortCode:(NSArray*) shortCode;
@end


@interface GSFindMatchRequest : GSRequest
-(void) setCallback:(void (^)(GSFindMatchResponse*))callback;
-(void) setAction:(NSString*) action;
-(void) setMatchGroup:(NSString*) matchGroup;
-(void) setMatchShortCode:(NSString*) matchShortCode;
-(void) setSkill:(NSNumber*) skill;
@end


@interface GSFindPendingMatchesRequest : GSRequest
-(void) setCallback:(void (^)(GSFindPendingMatchesResponse*))callback;
-(void) setMatchGroup:(NSString*) matchGroup;
-(void) setMatchShortCode:(NSString*) matchShortCode;
-(void) setMaxMatchesToFind:(NSNumber*) maxMatchesToFind;
@end


@interface GSGameCenterConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setDisplayName:(NSString*) displayName;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setExternalPlayerId:(NSString*) externalPlayerId;
-(void) setPublicKeyUrl:(NSString*) publicKeyUrl;
-(void) setSalt:(NSString*) salt;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSignature:(NSString*) signature;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
-(void) setTimestamp:(NSNumber*) timestamp;
@end


@interface GSGetChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSGetChallengeResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setMessage:(NSString*) message;
@end


@interface GSGetDownloadableRequest : GSRequest
-(void) setCallback:(void (^)(GSGetDownloadableResponse*))callback;
-(void) setShortCode:(NSString*) shortCode;
@end


@interface GSGetLeaderboardEntriesRequest : GSRequest
-(void) setCallback:(void (^)(GSGetLeaderboardEntriesResponse*))callback;
-(void) setChallenges:(NSArray*) challenges;
-(void) setInverseSocial:(BOOL) inverseSocial;
-(void) setLeaderboards:(NSArray*) leaderboards;
-(void) setPlayer:(NSString*) player;
-(void) setSocial:(BOOL) social;
-(void) setTeamTypes:(NSArray*) teamTypes;
@end


@interface GSGetMessageRequest : GSRequest
-(void) setCallback:(void (^)(GSGetMessageResponse*))callback;
-(void) setMessageId:(NSString*) messageId;
@end


@interface GSGetMyTeamsRequest : GSRequest
-(void) setCallback:(void (^)(GSGetMyTeamsResponse*))callback;
-(void) setOwnedOnly:(BOOL) ownedOnly;
-(void) setTeamTypes:(NSArray*) teamTypes;
@end


@interface GSGetPropertyRequest : GSRequest
-(void) setCallback:(void (^)(GSGetPropertyResponse*))callback;
-(void) setPropertyShortCode:(NSString*) propertyShortCode;
@end


@interface GSGetPropertySetRequest : GSRequest
-(void) setCallback:(void (^)(GSGetPropertySetResponse*))callback;
-(void) setPropertySetShortCode:(NSString*) propertySetShortCode;
@end


@interface GSGetTeamRequest : GSRequest
-(void) setCallback:(void (^)(GSGetTeamResponse*))callback;
-(void) setOwnerId:(NSString*) ownerId;
-(void) setTeamId:(NSString*) teamId;
-(void) setTeamType:(NSString*) teamType;
@end


@interface GSGetUploadUrlRequest : GSRequest
-(void) setCallback:(void (^)(GSGetUploadUrlResponse*))callback;
-(void) setUploadData:(NSDictionary*) uploadData;
@end


@interface GSGetUploadedRequest : GSRequest
-(void) setCallback:(void (^)(GSGetUploadedResponse*))callback;
-(void) setUploadId:(NSString*) uploadId;
@end


@interface GSGooglePlayBuyGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*))callback;
-(void) setCurrencyCode:(NSString*) currencyCode;
-(void) setSignature:(NSString*) signature;
-(void) setSignedData:(NSString*) signedData;
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice;
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer;
@end


@interface GSGooglePlayConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setCode:(NSString*) code;
-(void) setDisplayName:(NSString*) displayName;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setGooglePlusScope:(BOOL) googlePlusScope;
-(void) setProfileScope:(BOOL) profileScope;
-(void) setRedirectUri:(NSString*) redirectUri;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSGooglePlusConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setCode:(NSString*) code;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setRedirectUri:(NSString*) redirectUri;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSIOSBuyGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*))callback;
-(void) setCurrencyCode:(NSString*) currencyCode;
-(void) setReceipt:(NSString*) receipt;
-(void) setSandbox:(BOOL) sandbox;
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice;
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer;
@end


@interface GSJoinChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSJoinChallengeResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setEligibility:(NSDictionary*) eligibility;
-(void) setMessage:(NSString*) message;
@end


@interface GSJoinPendingMatchRequest : GSRequest
-(void) setCallback:(void (^)(GSJoinPendingMatchResponse*))callback;
-(void) setMatchGroup:(NSString*) matchGroup;
-(void) setMatchShortCode:(NSString*) matchShortCode;
-(void) setPendingMatchId:(NSString*) pendingMatchId;
@end


@interface GSJoinTeamRequest : GSRequest
-(void) setCallback:(void (^)(GSJoinTeamResponse*))callback;
-(void) setOwnerId:(NSString*) ownerId;
-(void) setTeamId:(NSString*) teamId;
-(void) setTeamType:(NSString*) teamType;
@end


@interface GSKongregateConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setGameAuthToken:(NSString*) gameAuthToken;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
-(void) setUserId:(NSString*) userId;
@end


@interface GSLeaderboardDataRequest : GSRequest
-(void) setCallback:(void (^)(GSLeaderboardDataResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setDontErrorOnNotSocial:(BOOL) dontErrorOnNotSocial;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setFriendIds:(NSArray*) friendIds;
-(void) setIncludeFirst:(NSNumber*) includeFirst;
-(void) setIncludeLast:(NSNumber*) includeLast;
-(void) setInverseSocial:(BOOL) inverseSocial;
-(void) setLeaderboardShortCode:(NSString*) leaderboardShortCode;
-(void) setOffset:(NSNumber*) offset;
-(void) setSocial:(BOOL) social;
-(void) setTeamIds:(NSArray*) teamIds;
-(void) setTeamTypes:(NSArray*) teamTypes;
@end


@interface GSLeaderboardsEntriesRequest : GSRequest
-(void) setCallback:(void (^)(GSLeaderboardsEntriesResponse*))callback;
-(void) setChallenges:(NSArray*) challenges;
-(void) setInverseSocial:(BOOL) inverseSocial;
-(void) setLeaderboards:(NSArray*) leaderboards;
-(void) setPlayer:(NSString*) player;
-(void) setSocial:(BOOL) social;
-(void) setTeamTypes:(NSArray*) teamTypes;
@end


@interface GSLeaveTeamRequest : GSRequest
-(void) setCallback:(void (^)(GSLeaveTeamResponse*))callback;
-(void) setOwnerId:(NSString*) ownerId;
-(void) setTeamId:(NSString*) teamId;
-(void) setTeamType:(NSString*) teamType;
@end


@interface GSListAchievementsRequest : GSRequest
-(void) setCallback:(void (^)(GSListAchievementsResponse*))callback;
@end


@interface GSListBulkJobsAdminRequest : GSRequest
-(void) setCallback:(void (^)(GSListBulkJobsAdminResponse*))callback;
-(void) setBulkJobIds:(NSArray*) bulkJobIds;
@end


@interface GSListChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSListChallengeResponse*))callback;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setOffset:(NSNumber*) offset;
-(void) setShortCode:(NSString*) shortCode;
-(void) setState:(NSString*) state;
-(void) setStates:(NSArray*) states;
@end


@interface GSListChallengeTypeRequest : GSRequest
-(void) setCallback:(void (^)(GSListChallengeTypeResponse*))callback;
@end


@interface GSListGameFriendsRequest : GSRequest
-(void) setCallback:(void (^)(GSListGameFriendsResponse*))callback;
@end


@interface GSListInviteFriendsRequest : GSRequest
-(void) setCallback:(void (^)(GSListInviteFriendsResponse*))callback;
@end


@interface GSListLeaderboardsRequest : GSRequest
-(void) setCallback:(void (^)(GSListLeaderboardsResponse*))callback;
@end


@interface GSListMessageDetailRequest : GSRequest
-(void) setCallback:(void (^)(GSListMessageDetailResponse*))callback;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setInclude:(NSString*) include;
-(void) setOffset:(NSNumber*) offset;
-(void) setStatus:(NSString*) status;
@end


@interface GSListMessageRequest : GSRequest
-(void) setCallback:(void (^)(GSListMessageResponse*))callback;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setInclude:(NSString*) include;
-(void) setOffset:(NSNumber*) offset;
@end


@interface GSListMessageSummaryRequest : GSRequest
-(void) setCallback:(void (^)(GSListMessageSummaryResponse*))callback;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setOffset:(NSNumber*) offset;
@end


@interface GSListTeamChatRequest : GSRequest
-(void) setCallback:(void (^)(GSListTeamChatResponse*))callback;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setOffset:(NSNumber*) offset;
-(void) setOwnerId:(NSString*) ownerId;
-(void) setTeamId:(NSString*) teamId;
-(void) setTeamType:(NSString*) teamType;
@end


@interface GSListTeamsRequest : GSRequest
-(void) setCallback:(void (^)(GSListTeamsResponse*))callback;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setOffset:(NSNumber*) offset;
-(void) setTeamNameFilter:(NSString*) teamNameFilter;
-(void) setTeamTypeFilter:(NSString*) teamTypeFilter;
@end


@interface GSListTransactionsRequest : GSRequest
-(void) setCallback:(void (^)(GSListTransactionsResponse*))callback;
-(void) setDateFrom:(NSDate*) dateFrom;
-(void) setDateTo:(NSDate*) dateTo;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setInclude:(NSString*) include;
-(void) setOffset:(NSNumber*) offset;
@end


@interface GSListVirtualGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSListVirtualGoodsResponse*))callback;
-(void) setIncludeDisabled:(BOOL) includeDisabled;
-(void) setTags:(NSArray*) tags;
@end


@interface GSLogChallengeEventRequest : GSRequest
-(void) setCallback:(void (^)(GSLogChallengeEventResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setEventKey:(NSString*) eventKey;
-(void) setEventAttribute:(NSString*)shortCode withNumber:(NSNumber*) value;
-(void) setEventAttribute:(NSString*)shortCode withString:(NSString*) value;
-(void) setEventAttribute:(NSString*)shortCode withDictionary:(NSDictionary*) value;
@end


@interface GSLogEventRequest : GSRequest
-(void) setCallback:(void (^)(GSLogEventResponse*))callback;
-(void) setEventKey:(NSString*) eventKey;
-(void) setEventAttribute:(NSString*)shortCode withNumber:(NSNumber*) value;
-(void) setEventAttribute:(NSString*)shortCode withString:(NSString*) value;
-(void) setEventAttribute:(NSString*)shortCode withDictionary:(NSDictionary*) value;
@end


@interface GSMatchDetailsRequest : GSRequest
-(void) setCallback:(void (^)(GSMatchDetailsResponse*))callback;
-(void) setMatchId:(NSString*) matchId;
-(void) setRealtimeEnabled:(BOOL) realtimeEnabled;
@end


@interface GSMatchmakingRequest : GSRequest
-(void) setCallback:(void (^)(GSMatchmakingResponse*))callback;
-(void) setAction:(NSString*) action;
-(void) setCustomQuery:(NSDictionary*) customQuery;
-(void) setMatchData:(NSDictionary*) matchData;
-(void) setMatchGroup:(NSString*) matchGroup;
-(void) setMatchShortCode:(NSString*) matchShortCode;
-(void) setParticipantData:(NSDictionary*) participantData;
-(void) setSkill:(NSNumber*) skill;
@end


@interface GSNXConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccountPerLoginId:(BOOL) accountPerLoginId;
-(void) setDisplayName:(NSString*) displayName;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setNsaIdToken:(NSString*) nsaIdToken;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSPSNConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAuthorizationCode:(NSString*) authorizationCode;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setRedirectUri:(NSString*) redirectUri;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSPsnBuyGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*))callback;
-(void) setAuthorizationCode:(NSString*) authorizationCode;
-(void) setCurrencyCode:(NSString*) currencyCode;
-(void) setEntitlementLabel:(NSString*) entitlementLabel;
-(void) setRedirectUri:(NSString*) redirectUri;
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice;
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer;
-(void) setUseCount:(NSNumber*) useCount;
@end


@interface GSPushRegistrationRequest : GSRequest
-(void) setCallback:(void (^)(GSPushRegistrationResponse*))callback;
-(void) setDeviceOS:(NSString*) deviceOS;
-(void) setPushId:(NSString*) pushId;
@end


@interface GSQQConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSRegistrationRequest : GSRequest
-(void) setCallback:(void (^)(GSRegistrationResponse*))callback;
-(void) setDisplayName:(NSString*) displayName;
-(void) setPassword:(NSString*) password;
-(void) setSegments:(NSDictionary*) segments;
-(void) setUserName:(NSString*) userName;
@end


@interface GSRevokePurchaseGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSRevokePurchaseGoodsResponse*))callback;
-(void) setPlayerId:(NSString*) playerId;
-(void) setStoreType:(NSString*) storeType;
-(void) setTransactionIds:(NSArray*) transactionIds;
@end


@interface GSScheduleBulkJobAdminRequest : GSRequest
-(void) setCallback:(void (^)(GSScheduleBulkJobAdminResponse*))callback;
-(void) setData:(NSDictionary*) data;
-(void) setModuleShortCode:(NSString*) moduleShortCode;
-(void) setPlayerQuery:(NSDictionary*) playerQuery;
-(void) setScheduledTime:(NSDate*) scheduledTime;
-(void) setScript:(NSString*) script;
@end


@interface GSSendFriendMessageRequest : GSRequest
-(void) setCallback:(void (^)(GSSendFriendMessageResponse*))callback;
-(void) setFriendIds:(NSArray*) friendIds;
-(void) setMessage:(NSString*) message;
@end


@interface GSSendTeamChatMessageRequest : GSRequest
-(void) setCallback:(void (^)(GSSendTeamChatMessageResponse*))callback;
-(void) setMessage:(NSString*) message;
-(void) setOwnerId:(NSString*) ownerId;
-(void) setTeamId:(NSString*) teamId;
-(void) setTeamType:(NSString*) teamType;
@end


@interface GSSocialDisconnectRequest : GSRequest
-(void) setCallback:(void (^)(GSSocialDisconnectResponse*))callback;
-(void) setSystemId:(NSString*) systemId;
@end


@interface GSSocialLeaderboardDataRequest : GSRequest
-(void) setCallback:(void (^)(GSLeaderboardDataResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setDontErrorOnNotSocial:(BOOL) dontErrorOnNotSocial;
-(void) setEntryCount:(NSNumber*) entryCount;
-(void) setFriendIds:(NSArray*) friendIds;
-(void) setIncludeFirst:(NSNumber*) includeFirst;
-(void) setIncludeLast:(NSNumber*) includeLast;
-(void) setInverseSocial:(BOOL) inverseSocial;
-(void) setLeaderboardShortCode:(NSString*) leaderboardShortCode;
-(void) setOffset:(NSNumber*) offset;
-(void) setSocial:(BOOL) social;
-(void) setTeamIds:(NSArray*) teamIds;
-(void) setTeamTypes:(NSArray*) teamTypes;
@end


@interface GSSocialStatusRequest : GSRequest
-(void) setCallback:(void (^)(GSSocialStatusResponse*))callback;
@end


@interface GSSteamBuyGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*))callback;
-(void) setCurrencyCode:(NSString*) currencyCode;
-(void) setOrderId:(NSString*) orderId;
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice;
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer;
@end


@interface GSSteamConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSessionTicket:(NSString*) sessionTicket;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSTwitchConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSTwitterConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessSecret:(NSString*) accessSecret;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSUpdateMessageRequest : GSRequest
-(void) setCallback:(void (^)(GSUpdateMessageResponse*))callback;
-(void) setMessageId:(NSString*) messageId;
-(void) setStatus:(NSString*) status;
@end


@interface GSViberConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setDoNotRegisterForPush:(BOOL) doNotRegisterForPush;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSWeChatConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setAccessToken:(NSString*) accessToken;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setOpenId:(NSString*) openId;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSWindowsBuyGoodsRequest : GSRequest
-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*))callback;
-(void) setCurrencyCode:(NSString*) currencyCode;
-(void) setPlatform:(NSString*) platform;
-(void) setReceipt:(NSString*) receipt;
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice;
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer;
@end


@interface GSWithdrawChallengeRequest : GSRequest
-(void) setCallback:(void (^)(GSWithdrawChallengeResponse*))callback;
-(void) setChallengeInstanceId:(NSString*) challengeInstanceId;
-(void) setMessage:(NSString*) message;
@end


@interface GSXBOXLiveConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setDisplayName:(NSString*) displayName;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSegments:(NSDictionary*) segments;
-(void) setStsTokenString:(NSString*) stsTokenString;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
@end


@interface GSXboxOneConnectRequest : GSRequest
-(void) setCallback:(void (^)(GSAuthenticationResponse*))callback;
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer;
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch;
-(void) setSandbox:(NSString*) sandbox;
-(void) setSegments:(NSDictionary*) segments;
-(void) setSwitchIfPossible:(BOOL) switchIfPossible;
-(void) setSyncDisplayName:(BOOL) syncDisplayName;
-(void) setToken:(NSString*) token;
@end


@interface GSMessageListener : NSObject
	-(void) processMessage:(NSDictionary*) message withType:(NSString*) type;
	-(void) onMessage:(void (^)(GSMessage*))messageListener;
	-(void) onGSAchievementEarnedMessage:(void (^)(GSAchievementEarnedMessage*))GSachievementEarnedMessageListener;
	-(void) onGSChallengeAcceptedMessage:(void (^)(GSChallengeAcceptedMessage*))GSchallengeAcceptedMessageListener;
	-(void) onGSChallengeChangedMessage:(void (^)(GSChallengeChangedMessage*))GSchallengeChangedMessageListener;
	-(void) onGSChallengeChatMessage:(void (^)(GSChallengeChatMessage*))GSchallengeChatMessageListener;
	-(void) onGSChallengeDeclinedMessage:(void (^)(GSChallengeDeclinedMessage*))GSchallengeDeclinedMessageListener;
	-(void) onGSChallengeDrawnMessage:(void (^)(GSChallengeDrawnMessage*))GSchallengeDrawnMessageListener;
	-(void) onGSChallengeExpiredMessage:(void (^)(GSChallengeExpiredMessage*))GSchallengeExpiredMessageListener;
	-(void) onGSChallengeIssuedMessage:(void (^)(GSChallengeIssuedMessage*))GSchallengeIssuedMessageListener;
	-(void) onGSChallengeJoinedMessage:(void (^)(GSChallengeJoinedMessage*))GSchallengeJoinedMessageListener;
	-(void) onGSChallengeLapsedMessage:(void (^)(GSChallengeLapsedMessage*))GSchallengeLapsedMessageListener;
	-(void) onGSChallengeLostMessage:(void (^)(GSChallengeLostMessage*))GSchallengeLostMessageListener;
	-(void) onGSChallengeStartedMessage:(void (^)(GSChallengeStartedMessage*))GSchallengeStartedMessageListener;
	-(void) onGSChallengeTurnTakenMessage:(void (^)(GSChallengeTurnTakenMessage*))GSchallengeTurnTakenMessageListener;
	-(void) onGSChallengeWaitingMessage:(void (^)(GSChallengeWaitingMessage*))GSchallengeWaitingMessageListener;
	-(void) onGSChallengeWithdrawnMessage:(void (^)(GSChallengeWithdrawnMessage*))GSchallengeWithdrawnMessageListener;
	-(void) onGSChallengeWonMessage:(void (^)(GSChallengeWonMessage*))GSchallengeWonMessageListener;
	-(void) onGSFriendMessage:(void (^)(GSFriendMessage*))GSfriendMessageListener;
	-(void) onGSGlobalRankChangedMessage:(void (^)(GSGlobalRankChangedMessage*))GSglobalRankChangedMessageListener;
	-(void) onGSMatchFoundMessage:(void (^)(GSMatchFoundMessage*))GSmatchFoundMessageListener;
	-(void) onGSMatchNotFoundMessage:(void (^)(GSMatchNotFoundMessage*))GSmatchNotFoundMessageListener;
	-(void) onGSMatchUpdatedMessage:(void (^)(GSMatchUpdatedMessage*))GSmatchUpdatedMessageListener;
	-(void) onGSNewHighScoreMessage:(void (^)(GSNewHighScoreMessage*))GSnewHighScoreMessageListener;
	-(void) onGSNewTeamScoreMessage:(void (^)(GSNewTeamScoreMessage*))GSnewTeamScoreMessageListener;
	-(void) onGSScriptMessage:(void (^)(GSScriptMessage*))GSscriptMessageListener;
	-(void) onGSSessionTerminatedMessage:(void (^)(GSSessionTerminatedMessage*))GSsessionTerminatedMessageListener;
	-(void) onGSSocialRankChangedMessage:(void (^)(GSSocialRankChangedMessage*))GSsocialRankChangedMessageListener;
	-(void) onGSTeamChatMessage:(void (^)(GSTeamChatMessage*))GSteamChatMessageListener;
	-(void) onGSTeamRankChangedMessage:(void (^)(GSTeamRankChangedMessage*))GSteamRankChangedMessageListener;
	-(void) onGSUploadCompleteMessage:(void (^)(GSUploadCompleteMessage*))GSuploadCompleteMessageListener;
@end

@interface GSRequestBuilder : NSObject
	+(GSRequest*) buildRequest:(NSDictionary*)data;
@end

#endif

