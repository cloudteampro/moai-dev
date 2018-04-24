
#import "GSAPI.h"

@implementation GSBulkJob

-(NSNumber*) getActualCount{
	return [self._data objectForKey:@"actualCount"];
}

-(NSDate*) getCompleted{
	return [self getDateFromString:[self._data objectForKey:@"completed"]];
}

-(NSDate*) getCreated{
	return [self getDateFromString:[self._data objectForKey:@"created"]];
}

-(NSDictionary*) getData{
	return [self._data objectForKey:@"data"];
}

-(NSNumber*) getDoneCount{
	return [self._data objectForKey:@"doneCount"];
}

-(NSNumber*) getErrorCount{
	return [self._data objectForKey:@"errorCount"];
}

-(NSNumber*) getEstimatedCount{
	return [self._data objectForKey:@"estimatedCount"];
}

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(NSString*) getModuleShortCode{
	return [self._data objectForKey:@"moduleShortCode"];
}

-(NSDictionary*) getPlayerQuery{
	return [self._data objectForKey:@"playerQuery"];
}

-(NSDate*) getScheduledTime{
	return [self getDateFromString:[self._data objectForKey:@"scheduledTime"]];
}

-(NSString*) getScript{
	return [self._data objectForKey:@"script"];
}

-(NSDate*) getStarted{
	return [self getDateFromString:[self._data objectForKey:@"started"]];
}

-(NSString*) getState{
	return [self._data objectForKey:@"state"];
}
@end
@implementation GSInvitableFriend

-(NSString*) getDisplayName{
	return [self._data objectForKey:@"displayName"];
}

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(NSString*) getProfilePic{
	return [self._data objectForKey:@"profilePic"];
}
@end
@implementation GSAchievement

-(NSString*) getDescription{
	return [self._data objectForKey:@"description"];
}

-(BOOL) getEarned{
	return [[self._data objectForKey:@"earned"]  boolValue];
}

-(NSString*) getName{
	return [self._data objectForKey:@"name"];
}

-(NSDictionary*) getPropertySet{
	return [self._data objectForKey:@"propertySet"];
}

-(NSString*) getShortCode{
	return [self._data objectForKey:@"shortCode"];
}
@end
@implementation GSBundledGood

-(NSNumber*) getQty{
	return [self._data objectForKey:@"qty"];
}

-(NSString*) getShortCode{
	return [self._data objectForKey:@"shortCode"];
}
@end
@implementation GSVirtualGood

-(NSString*) getWP8StoreProductId{
	return [self._data objectForKey:@"WP8StoreProductId"];
}

-(NSString*) getAmazonStoreProductId{
	return [self._data objectForKey:@"amazonStoreProductId"];
}

-(NSNumber*) getBaseCurrency1Cost{
	return [self._data objectForKey:@"baseCurrency1Cost"];
}

-(NSNumber*) getBaseCurrency2Cost{
	return [self._data objectForKey:@"baseCurrency2Cost"];
}

-(NSNumber*) getBaseCurrency3Cost{
	return [self._data objectForKey:@"baseCurrency3Cost"];
}

-(NSNumber*) getBaseCurrency4Cost{
	return [self._data objectForKey:@"baseCurrency4Cost"];
}

-(NSNumber*) getBaseCurrency5Cost{
	return [self._data objectForKey:@"baseCurrency5Cost"];
}

-(NSNumber*) getBaseCurrency6Cost{
	return [self._data objectForKey:@"baseCurrency6Cost"];
}

-(NSDictionary*) getBaseCurrencyCosts{
	return [self._data objectForKey:@"baseCurrencyCosts"];
}

-(NSArray*) getBundledGoods{
	if(![self._data objectForKey:@"bundledGoods"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"bundledGoods"]) {
		[ret addObject:[[GSBundledGood alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSNumber*) getCurrency1Cost{
	return [self._data objectForKey:@"currency1Cost"];
}

-(NSNumber*) getCurrency2Cost{
	return [self._data objectForKey:@"currency2Cost"];
}

-(NSNumber*) getCurrency3Cost{
	return [self._data objectForKey:@"currency3Cost"];
}

-(NSNumber*) getCurrency4Cost{
	return [self._data objectForKey:@"currency4Cost"];
}

-(NSNumber*) getCurrency5Cost{
	return [self._data objectForKey:@"currency5Cost"];
}

-(NSNumber*) getCurrency6Cost{
	return [self._data objectForKey:@"currency6Cost"];
}

-(NSDictionary*) getCurrencyCosts{
	return [self._data objectForKey:@"currencyCosts"];
}

-(NSString*) getDescription{
	return [self._data objectForKey:@"description"];
}

-(BOOL) getDisabled{
	return [[self._data objectForKey:@"disabled"]  boolValue];
}

-(NSString*) getGooglePlayProductId{
	return [self._data objectForKey:@"googlePlayProductId"];
}

-(NSString*) getIosAppStoreProductId{
	return [self._data objectForKey:@"iosAppStoreProductId"];
}

-(NSNumber*) getMaxQuantity{
	return [self._data objectForKey:@"maxQuantity"];
}

-(NSString*) getName{
	return [self._data objectForKey:@"name"];
}

-(NSDictionary*) getPropertySet{
	return [self._data objectForKey:@"propertySet"];
}

-(NSString*) getPsnStoreProductId{
	return [self._data objectForKey:@"psnStoreProductId"];
}

-(NSNumber*) getSegmentedCurrency1Cost{
	return [self._data objectForKey:@"segmentedCurrency1Cost"];
}

-(NSNumber*) getSegmentedCurrency2Cost{
	return [self._data objectForKey:@"segmentedCurrency2Cost"];
}

-(NSNumber*) getSegmentedCurrency3Cost{
	return [self._data objectForKey:@"segmentedCurrency3Cost"];
}

-(NSNumber*) getSegmentedCurrency4Cost{
	return [self._data objectForKey:@"segmentedCurrency4Cost"];
}

-(NSNumber*) getSegmentedCurrency5Cost{
	return [self._data objectForKey:@"segmentedCurrency5Cost"];
}

-(NSNumber*) getSegmentedCurrency6Cost{
	return [self._data objectForKey:@"segmentedCurrency6Cost"];
}

-(NSDictionary*) getSegmentedCurrencyCosts{
	return [self._data objectForKey:@"segmentedCurrencyCosts"];
}

-(NSString*) getShortCode{
	return [self._data objectForKey:@"shortCode"];
}

-(NSString*) getSteamStoreProductId{
	return [self._data objectForKey:@"steamStoreProductId"];
}

-(NSString*) getTags{
	return [self._data objectForKey:@"tags"];
}

-(NSString*) getType{
	return [self._data objectForKey:@"type"];
}

-(NSString*) getW8StoreProductId{
	return [self._data objectForKey:@"w8StoreProductId"];
}
@end
@implementation GSPlayer

		
-(NSString*) getAchievements{
	return [self._data objectForKey:@"achievements"];
}

-(NSString*) getDisplayName{
	return [self._data objectForKey:@"displayName"];
}

-(NSDictionary*) getExternalIds{
	return [self._data objectForKey:@"externalIds"];
}

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(BOOL) getOnline{
	return [[self._data objectForKey:@"online"]  boolValue];
}

-(NSDictionary*) getScriptData{
	return [self._data objectForKey:@"scriptData"];
}

		
-(NSString*) getVirtualGoods{
	return [self._data objectForKey:@"virtualGoods"];
}
@end
@implementation GSTeam

-(NSArray*) getMembers{
	if(![self._data objectForKey:@"members"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"members"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(GSPlayer*) getOwner{
	if(![self._data objectForKey:@"owner"]){
		return nil;
	}
	return [[GSPlayer alloc] initWithData:[self._data objectForKey:@"owner"]];
}

-(NSString*) getTeamId{
	return [self._data objectForKey:@"teamId"];
}

-(NSString*) getTeamName{
	return [self._data objectForKey:@"teamName"];
}

-(NSString*) getTeamType{
	return [self._data objectForKey:@"teamType"];
}
@end
@implementation GSLeaderboard

-(NSString*) getDescription{
	return [self._data objectForKey:@"description"];
}

-(NSString*) getName{
	return [self._data objectForKey:@"name"];
}

-(NSDictionary*) getPropertySet{
	return [self._data objectForKey:@"propertySet"];
}

-(NSString*) getShortCode{
	return [self._data objectForKey:@"shortCode"];
}
@end
@implementation GSChatMessage

-(NSString*) getFromId{
	return [self._data objectForKey:@"fromId"];
}

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSDate*) getWhen{
	return [self getDateFromString:[self._data objectForKey:@"when"]];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSPlayerDetail

-(NSDictionary*) getExternalIds{
	return [self._data objectForKey:@"externalIds"];
}

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(NSString*) getName{
	return [self._data objectForKey:@"name"];
}
@end
@implementation GSUploadData

-(NSString*) getFileName{
	return [self._data objectForKey:@"fileName"];
}

-(NSString*) getPlayerId{
	return [self._data objectForKey:@"playerId"];
}
@end
@implementation GSChallengeType

-(NSString*) getChallengeShortCode{
	return [self._data objectForKey:@"challengeShortCode"];
}

-(NSString*) getDescription{
	return [self._data objectForKey:@"description"];
}

-(NSString*) getGetleaderboardName{
	return [self._data objectForKey:@"getleaderboardName"];
}

-(NSString*) getName{
	return [self._data objectForKey:@"name"];
}

-(NSString*) getTags{
	return [self._data objectForKey:@"tags"];
}
@end
@implementation GSBoughtitem

-(NSNumber*) getQuantity{
	return [self._data objectForKey:@"quantity"];
}

-(NSString*) getShortCode{
	return [self._data objectForKey:@"shortCode"];
}
@end
@implementation GSPlayerMessage

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(NSDictionary*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(BOOL) getSeen{
	return [[self._data objectForKey:@"seen"]  boolValue];
}

-(NSString*) getStatus{
	return [self._data objectForKey:@"status"];
}

-(NSDate*) getWhen{
	return [self getDateFromString:[self._data objectForKey:@"when"]];
}
@end
@implementation GSMatchedPlayer

-(NSDictionary*) getLocation{
	return [self._data objectForKey:@"location"];
}

-(NSDictionary*) getParticipantData{
	return [self._data objectForKey:@"participantData"];
}

-(NSString*) getPlayerId{
	return [self._data objectForKey:@"playerId"];
}

-(NSNumber*) getSkill{
	return [self._data objectForKey:@"skill"];
}
@end
@implementation GSPendingMatch

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(NSDictionary*) getMatchData{
	return [self._data objectForKey:@"matchData"];
}

-(NSString*) getMatchGroup{
	return [self._data objectForKey:@"matchGroup"];
}

-(NSString*) getMatchShortCode{
	return [self._data objectForKey:@"matchShortCode"];
}

-(NSArray*) getMatchedPlayers{
	if(![self._data objectForKey:@"matchedPlayers"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"matchedPlayers"]) {
		[ret addObject:[[GSMatchedPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSNumber*) getSkill{
	return [self._data objectForKey:@"skill"];
}
@end
@implementation GSParticipant

		
-(NSString*) getAchievements{
	return [self._data objectForKey:@"achievements"];
}

-(NSString*) getDisplayName{
	return [self._data objectForKey:@"displayName"];
}

-(NSDictionary*) getExternalIds{
	return [self._data objectForKey:@"externalIds"];
}

-(NSString*) getId{
	return [self._data objectForKey:@"id"];
}

-(BOOL) getOnline{
	return [[self._data objectForKey:@"online"]  boolValue];
}

-(NSDictionary*) getParticipantData{
	return [self._data objectForKey:@"participantData"];
}

-(NSNumber*) getPeerId{
	return [self._data objectForKey:@"peerId"];
}

-(NSDictionary*) getScriptData{
	return [self._data objectForKey:@"scriptData"];
}

		
-(NSString*) getVirtualGoods{
	return [self._data objectForKey:@"virtualGoods"];
}
@end
@implementation GSPlayerTransactionItem

-(NSNumber*) getAmount{
	return [self._data objectForKey:@"amount"];
}

-(NSNumber*) getNewValue{
	return [self._data objectForKey:@"newValue"];
}

-(NSString*) getType{
	return [self._data objectForKey:@"type"];
}
@end
@implementation GSPlayerTransaction

-(NSArray*) getItems{
	if(![self._data objectForKey:@"items"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"items"]) {
		[ret addObject:[[GSPlayerTransactionItem alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSString*) getOriginalRequestId{
	return [self._data objectForKey:@"originalRequestId"];
}

-(NSString*) getPlayerId{
	return [self._data objectForKey:@"playerId"];
}

-(NSString*) getReason{
	return [self._data objectForKey:@"reason"];
}

-(NSDate*) getRevokeDate{
	return [self getDateFromString:[self._data objectForKey:@"revokeDate"]];
}

-(BOOL) getRevoked{
	return [[self._data objectForKey:@"revoked"]  boolValue];
}

-(NSString*) getScript{
	return [self._data objectForKey:@"script"];
}

-(NSString*) getScriptType{
	return [self._data objectForKey:@"scriptType"];
}

-(NSString*) getTransactionId{
	return [self._data objectForKey:@"transactionId"];
}

-(NSDate*) getWhen{
	return [self getDateFromString:[self._data objectForKey:@"when"]];
}
@end
@implementation GSPlayerTurnCount

-(NSString*) getCount{
	return [self._data objectForKey:@"count"];
}

-(NSString*) getPlayerId{
	return [self._data objectForKey:@"playerId"];
}
@end
@implementation GSChallenge

-(NSArray*) getAccepted{
	if(![self._data objectForKey:@"accepted"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"accepted"]) {
		[ret addObject:[[GSPlayerDetail alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSString*) getChallengeId{
	return [self._data objectForKey:@"challengeId"];
}

-(NSString*) getChallengeMessage{
	return [self._data objectForKey:@"challengeMessage"];
}

-(NSString*) getChallengeName{
	return [self._data objectForKey:@"challengeName"];
}

-(NSArray*) getChallenged{
	if(![self._data objectForKey:@"challenged"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"challenged"]) {
		[ret addObject:[[GSPlayerDetail alloc] initWithData:object]];
	}
	
	return ret;
}

-(GSPlayerDetail*) getChallenger{
	if(![self._data objectForKey:@"challenger"]){
		return nil;
	}
	return [[GSPlayerDetail alloc] initWithData:[self._data objectForKey:@"challenger"]];
}

-(NSNumber*) getCurrency1Wager{
	return [self._data objectForKey:@"currency1Wager"];
}

-(NSNumber*) getCurrency2Wager{
	return [self._data objectForKey:@"currency2Wager"];
}

-(NSNumber*) getCurrency3Wager{
	return [self._data objectForKey:@"currency3Wager"];
}

-(NSNumber*) getCurrency4Wager{
	return [self._data objectForKey:@"currency4Wager"];
}

-(NSNumber*) getCurrency5Wager{
	return [self._data objectForKey:@"currency5Wager"];
}

-(NSNumber*) getCurrency6Wager{
	return [self._data objectForKey:@"currency6Wager"];
}

-(NSDictionary*) getCurrencyWagers{
	return [self._data objectForKey:@"currencyWagers"];
}

-(NSArray*) getDeclined{
	if(![self._data objectForKey:@"declined"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"declined"]) {
		[ret addObject:[[GSPlayerDetail alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSDate*) getEndDate{
	return [self getDateFromString:[self._data objectForKey:@"endDate"]];
}

-(NSDate*) getExpiryDate{
	return [self getDateFromString:[self._data objectForKey:@"expiryDate"]];
}

-(NSNumber*) getMaxTurns{
	return [self._data objectForKey:@"maxTurns"];
}

-(NSString*) getNextPlayer{
	return [self._data objectForKey:@"nextPlayer"];
}

-(NSDictionary*) getScriptData{
	return [self._data objectForKey:@"scriptData"];
}

-(NSString*) getShortCode{
	return [self._data objectForKey:@"shortCode"];
}

-(NSDate*) getStartDate{
	return [self getDateFromString:[self._data objectForKey:@"startDate"]];
}

-(NSString*) getState{
	return [self._data objectForKey:@"state"];
}

-(NSArray*) getTurnCount{
	if(![self._data objectForKey:@"turnCount"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"turnCount"]) {
		[ret addObject:[[GSPlayerTurnCount alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSLeaderboardData

-(NSString*) getCity{
	return [self._data objectForKey:@"city"];
}

-(NSString*) getCountry{
	return [self._data objectForKey:@"country"];
}

-(NSDictionary*) getExternalIds{
	return [self._data objectForKey:@"externalIds"];
}

-(NSNumber*) getRank{
	return [self._data objectForKey:@"rank"];
}

-(NSString*) getUserId{
	return [self._data objectForKey:@"userId"];
}

-(NSString*) getUserName{
	return [self._data objectForKey:@"userName"];
}

-(NSString*) getWhen{
	return [self._data objectForKey:@"when"];
}
-(NSNumber*)getNumberValue:(NSString*)shortCode{
	return [self._data objectForKey:shortCode];
}
-(NSString*)getStringValue:(NSString*)shortCode{
	return [self._data objectForKey:shortCode];
}
@end
@implementation GSLeaderboardRankDetails

-(NSArray*) getFriendsPassed{
	if(![self._data objectForKey:@"friendsPassed"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"friendsPassed"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSNumber*) getGlobalCount{
	return [self._data objectForKey:@"globalCount"];
}

-(NSNumber*) getGlobalFrom{
	return [self._data objectForKey:@"globalFrom"];
}

-(NSNumber*) getGlobalFromPercent{
	return [self._data objectForKey:@"globalFromPercent"];
}

-(NSNumber*) getGlobalTo{
	return [self._data objectForKey:@"globalTo"];
}

-(NSNumber*) getGlobalToPercent{
	return [self._data objectForKey:@"globalToPercent"];
}

-(NSNumber*) getSocialCount{
	return [self._data objectForKey:@"socialCount"];
}

-(NSNumber*) getSocialFrom{
	return [self._data objectForKey:@"socialFrom"];
}

-(NSNumber*) getSocialFromPercent{
	return [self._data objectForKey:@"socialFromPercent"];
}

-(NSNumber*) getSocialTo{
	return [self._data objectForKey:@"socialTo"];
}

-(NSNumber*) getSocialToPercent{
	return [self._data objectForKey:@"socialToPercent"];
}

-(NSArray*) getTopNPassed{
	if(![self._data objectForKey:@"topNPassed"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"topNPassed"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSSocialStatus

-(BOOL) getActive{
	return [[self._data objectForKey:@"active"]  boolValue];
}

-(NSDate*) getExpires{
	return [self getDateFromString:[self._data objectForKey:@"expires"]];
}

-(NSString*) getSystemId{
	return [self._data objectForKey:@"systemId"];
}
@end
@implementation GSLocation

-(NSString*) getCity{
	return [self._data objectForKey:@"city"];
}

-(NSString*) getCountry{
	return [self._data objectForKey:@"country"];
}

-(NSNumber*) getLatitide{
	return [self._data objectForKey:@"latitide"];
}

-(NSNumber*) getLongditute{
	return [self._data objectForKey:@"longditute"];
}
@end

@implementation GSAcceptChallengeResponse

-(NSString*) getChallengeInstanceId{
	return [self._data objectForKey:@"challengeInstanceId"];
}
@end
@implementation GSAccountDetailsResponse

		
-(NSString*) getAchievements{
	return [self._data objectForKey:@"achievements"];
}

-(NSDictionary*) getCurrencies{
	return [self._data objectForKey:@"currencies"];
}

-(NSNumber*) getCurrency1{
	return [self._data objectForKey:@"currency1"];
}

-(NSNumber*) getCurrency2{
	return [self._data objectForKey:@"currency2"];
}

-(NSNumber*) getCurrency3{
	return [self._data objectForKey:@"currency3"];
}

-(NSNumber*) getCurrency4{
	return [self._data objectForKey:@"currency4"];
}

-(NSNumber*) getCurrency5{
	return [self._data objectForKey:@"currency5"];
}

-(NSNumber*) getCurrency6{
	return [self._data objectForKey:@"currency6"];
}

-(NSString*) getDisplayName{
	return [self._data objectForKey:@"displayName"];
}

-(NSDictionary*) getExternalIds{
	return [self._data objectForKey:@"externalIds"];
}

-(GSLocation*) getLocation{
	if(![self._data objectForKey:@"location"]){
		return nil;
	}
	return [[GSLocation alloc] initWithData:[self._data objectForKey:@"location"]];
}

-(NSDictionary*) getReservedCurrencies{
	return [self._data objectForKey:@"reservedCurrencies"];
}

-(NSDictionary*) getReservedCurrency1{
	return [self._data objectForKey:@"reservedCurrency1"];
}

-(NSDictionary*) getReservedCurrency2{
	return [self._data objectForKey:@"reservedCurrency2"];
}

-(NSDictionary*) getReservedCurrency3{
	return [self._data objectForKey:@"reservedCurrency3"];
}

-(NSDictionary*) getReservedCurrency4{
	return [self._data objectForKey:@"reservedCurrency4"];
}

-(NSDictionary*) getReservedCurrency5{
	return [self._data objectForKey:@"reservedCurrency5"];
}

-(NSDictionary*) getReservedCurrency6{
	return [self._data objectForKey:@"reservedCurrency6"];
}

-(NSString*) getUserId{
	return [self._data objectForKey:@"userId"];
}

-(NSDictionary*) getVirtualGoods{
	return [self._data objectForKey:@"virtualGoods"];
}
@end
@implementation GSAnalyticsResponse
@end
@implementation GSAroundMeLeaderboardResponse

-(NSString*) getChallengeInstanceId{
	return [self._data objectForKey:@"challengeInstanceId"];
}

-(NSArray*) getData{
	if(![self._data objectForKey:@"data"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"data"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSArray*) getFirst{
	if(![self._data objectForKey:@"first"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"first"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSArray*) getLast{
	if(![self._data objectForKey:@"last"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"last"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSString*) getLeaderboardShortCode{
	return [self._data objectForKey:@"leaderboardShortCode"];
}

-(BOOL) getSocial{
	return [[self._data objectForKey:@"social"]  boolValue];
}
@end
@implementation GSAuthenticationResponse

-(NSString*) getAuthToken{
	return [self._data objectForKey:@"authToken"];
}

-(NSString*) getDisplayName{
	return [self._data objectForKey:@"displayName"];
}

-(BOOL) getNewPlayer{
	return [[self._data objectForKey:@"newPlayer"]  boolValue];
}

-(GSPlayer*) getSwitchSummary{
	if(![self._data objectForKey:@"switchSummary"]){
		return nil;
	}
	return [[GSPlayer alloc] initWithData:[self._data objectForKey:@"switchSummary"]];
}

-(NSString*) getUserId{
	return [self._data objectForKey:@"userId"];
}
@end
@implementation GSBatchAdminResponse

-(NSDictionary*) getResponses{
	return [self._data objectForKey:@"responses"];
}
@end
@implementation GSBuyVirtualGoodResponse

-(NSArray*) getBoughtItems{
	if(![self._data objectForKey:@"boughtItems"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"boughtItems"]) {
		[ret addObject:[[GSBoughtitem alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSDictionary*) getCurrenciesAdded{
	return [self._data objectForKey:@"currenciesAdded"];
}

-(NSNumber*) getCurrency1Added{
	return [self._data objectForKey:@"currency1Added"];
}

-(NSNumber*) getCurrency2Added{
	return [self._data objectForKey:@"currency2Added"];
}

-(NSNumber*) getCurrency3Added{
	return [self._data objectForKey:@"currency3Added"];
}

-(NSNumber*) getCurrency4Added{
	return [self._data objectForKey:@"currency4Added"];
}

-(NSNumber*) getCurrency5Added{
	return [self._data objectForKey:@"currency5Added"];
}

-(NSNumber*) getCurrency6Added{
	return [self._data objectForKey:@"currency6Added"];
}

-(NSNumber*) getCurrencyConsumed{
	return [self._data objectForKey:@"currencyConsumed"];
}

-(NSString*) getCurrencyShortCode{
	return [self._data objectForKey:@"currencyShortCode"];
}

-(NSNumber*) getCurrencyType{
	return [self._data objectForKey:@"currencyType"];
}

		
-(NSString*) getInvalidItems{
	return [self._data objectForKey:@"invalidItems"];
}

		
-(NSString*) getTransactionIds{
	return [self._data objectForKey:@"transactionIds"];
}
@end
@implementation GSCancelBulkJobAdminResponse

-(NSArray*) getBulkJobs{
	if(![self._data objectForKey:@"bulkJobs"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"bulkJobs"]) {
		[ret addObject:[[GSBulkJob alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSChangeUserDetailsResponse
@end
@implementation GSChatOnChallengeResponse

-(NSString*) getChallengeInstanceId{
	return [self._data objectForKey:@"challengeInstanceId"];
}
@end
@implementation GSConsumeVirtualGoodResponse
@end
@implementation GSCreateChallengeResponse

-(NSString*) getChallengeInstanceId{
	return [self._data objectForKey:@"challengeInstanceId"];
}
@end
@implementation GSCreateTeamResponse

-(NSArray*) getMembers{
	if(![self._data objectForKey:@"members"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"members"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(GSPlayer*) getOwner{
	if(![self._data objectForKey:@"owner"]){
		return nil;
	}
	return [[GSPlayer alloc] initWithData:[self._data objectForKey:@"owner"]];
}

-(NSString*) getTeamId{
	return [self._data objectForKey:@"teamId"];
}

-(NSString*) getTeamName{
	return [self._data objectForKey:@"teamName"];
}

-(NSString*) getTeamType{
	return [self._data objectForKey:@"teamType"];
}
@end
@implementation GSDeclineChallengeResponse

-(NSString*) getChallengeInstanceId{
	return [self._data objectForKey:@"challengeInstanceId"];
}
@end
@implementation GSDismissMessageResponse
@end
@implementation GSDismissMultipleMessagesResponse

		
-(NSString*) getFailedDismissals{
	return [self._data objectForKey:@"failedDismissals"];
}

-(NSNumber*) getMessagesDismissed{
	return [self._data objectForKey:@"messagesDismissed"];
}
@end
@implementation GSDropTeamResponse
@end
@implementation GSEndSessionResponse

-(NSNumber*) getSessionDuration{
	return [self._data objectForKey:@"sessionDuration"];
}
@end
@implementation GSFindChallengeResponse

-(NSArray*) getChallengeInstances{
	if(![self._data objectForKey:@"challengeInstances"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"challengeInstances"]) {
		[ret addObject:[[GSChallenge alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSFindMatchResponse

-(NSString*) getAccessToken{
	return [self._data objectForKey:@"accessToken"];
}

-(NSString*) getHost{
	return [self._data objectForKey:@"host"];
}

-(NSDictionary*) getMatchData{
	return [self._data objectForKey:@"matchData"];
}

-(NSString*) getMatchId{
	return [self._data objectForKey:@"matchId"];
}

-(NSArray*) getOpponents{
	if(![self._data objectForKey:@"opponents"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"opponents"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSNumber*) getPeerId{
	return [self._data objectForKey:@"peerId"];
}

-(NSString*) getPlayerId{
	return [self._data objectForKey:@"playerId"];
}

-(NSNumber*) getPort{
	return [self._data objectForKey:@"port"];
}
@end
@implementation GSFindPendingMatchesResponse

-(NSArray*) getPendingMatches{
	if(![self._data objectForKey:@"pendingMatches"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"pendingMatches"]) {
		[ret addObject:[[GSPendingMatch alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSGameSparksErrorResponse
@end
@implementation GSGetChallengeResponse

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}
@end
@implementation GSGetDownloadableResponse

-(NSDate*) getLastModified{
	return [self getDateFromString:[self._data objectForKey:@"lastModified"]];
}

-(NSString*) getShortCode{
	return [self._data objectForKey:@"shortCode"];
}

-(NSNumber*) getSize{
	return [self._data objectForKey:@"size"];
}

-(NSString*) getUrl{
	return [self._data objectForKey:@"url"];
}
@end
@implementation GSGetLeaderboardEntriesResponse

-(NSDictionary*) getResults{
	return [self._data objectForKey:@"results"];
}
-(GSLeaderboardData*)getEntryForLeaderboard:(NSString*)shortCode{
	if(![self._data objectForKey:shortCode]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:shortCode]];
}
@end
@implementation GSGetMessageResponse

-(NSDictionary*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getStatus{
	return [self._data objectForKey:@"status"];
}
@end
@implementation GSGetMyTeamsResponse

-(NSArray*) getTeams{
	if(![self._data objectForKey:@"teams"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"teams"]) {
		[ret addObject:[[GSTeam alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSGetPropertyResponse

-(NSDictionary*) getProperty{
	return [self._data objectForKey:@"property"];
}
@end
@implementation GSGetPropertySetResponse

-(NSDictionary*) getPropertySet{
	return [self._data objectForKey:@"propertySet"];
}
@end
@implementation GSGetTeamResponse

-(NSArray*) getMembers{
	if(![self._data objectForKey:@"members"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"members"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(GSPlayer*) getOwner{
	if(![self._data objectForKey:@"owner"]){
		return nil;
	}
	return [[GSPlayer alloc] initWithData:[self._data objectForKey:@"owner"]];
}

-(NSString*) getTeamId{
	return [self._data objectForKey:@"teamId"];
}

-(NSString*) getTeamName{
	return [self._data objectForKey:@"teamName"];
}

-(NSString*) getTeamType{
	return [self._data objectForKey:@"teamType"];
}

-(NSArray*) getTeams{
	if(![self._data objectForKey:@"teams"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"teams"]) {
		[ret addObject:[[GSTeam alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSGetUploadUrlResponse

-(NSString*) getUrl{
	return [self._data objectForKey:@"url"];
}
@end
@implementation GSGetUploadedResponse

-(NSNumber*) getSize{
	return [self._data objectForKey:@"size"];
}

-(NSString*) getUrl{
	return [self._data objectForKey:@"url"];
}
@end
@implementation GSJoinChallengeResponse

-(BOOL) getJoined{
	return [[self._data objectForKey:@"joined"]  boolValue];
}
@end
@implementation GSJoinPendingMatchResponse

-(GSPendingMatch*) getPendingMatch{
	if(![self._data objectForKey:@"pendingMatch"]){
		return nil;
	}
	return [[GSPendingMatch alloc] initWithData:[self._data objectForKey:@"pendingMatch"]];
}
@end
@implementation GSJoinTeamResponse

-(NSArray*) getMembers{
	if(![self._data objectForKey:@"members"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"members"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(GSPlayer*) getOwner{
	if(![self._data objectForKey:@"owner"]){
		return nil;
	}
	return [[GSPlayer alloc] initWithData:[self._data objectForKey:@"owner"]];
}

-(NSString*) getTeamId{
	return [self._data objectForKey:@"teamId"];
}

-(NSString*) getTeamName{
	return [self._data objectForKey:@"teamName"];
}

-(NSString*) getTeamType{
	return [self._data objectForKey:@"teamType"];
}
@end
@implementation GSLeaderboardDataResponse

-(NSString*) getChallengeInstanceId{
	return [self._data objectForKey:@"challengeInstanceId"];
}

-(NSArray*) getData{
	if(![self._data objectForKey:@"data"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"data"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSArray*) getFirst{
	if(![self._data objectForKey:@"first"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"first"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSArray*) getLast{
	if(![self._data objectForKey:@"last"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"last"]) {
		[ret addObject:[[GSLeaderboardData alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSString*) getLeaderboardShortCode{
	return [self._data objectForKey:@"leaderboardShortCode"];
}
@end
@implementation GSLeaderboardsEntriesResponse

-(NSDictionary*) getResults{
	return [self._data objectForKey:@"results"];
}
@end
@implementation GSLeaveTeamResponse

-(NSArray*) getMembers{
	if(![self._data objectForKey:@"members"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"members"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(GSPlayer*) getOwner{
	if(![self._data objectForKey:@"owner"]){
		return nil;
	}
	return [[GSPlayer alloc] initWithData:[self._data objectForKey:@"owner"]];
}

-(NSString*) getTeamId{
	return [self._data objectForKey:@"teamId"];
}

-(NSString*) getTeamName{
	return [self._data objectForKey:@"teamName"];
}

-(NSString*) getTeamType{
	return [self._data objectForKey:@"teamType"];
}
@end
@implementation GSListAchievementsResponse

-(NSArray*) getAchievements{
	if(![self._data objectForKey:@"achievements"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"achievements"]) {
		[ret addObject:[[GSAchievement alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListBulkJobsAdminResponse

-(NSArray*) getBulkJobs{
	if(![self._data objectForKey:@"bulkJobs"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"bulkJobs"]) {
		[ret addObject:[[GSBulkJob alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListChallengeResponse

-(NSArray*) getChallengeInstances{
	if(![self._data objectForKey:@"challengeInstances"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"challengeInstances"]) {
		[ret addObject:[[GSChallenge alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListChallengeTypeResponse

-(NSArray*) getChallengeTemplates{
	if(![self._data objectForKey:@"challengeTemplates"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"challengeTemplates"]) {
		[ret addObject:[[GSChallengeType alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListGameFriendsResponse

-(NSArray*) getFriends{
	if(![self._data objectForKey:@"friends"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"friends"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListInviteFriendsResponse

-(NSArray*) getFriends{
	if(![self._data objectForKey:@"friends"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"friends"]) {
		[ret addObject:[[GSInvitableFriend alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListLeaderboardsResponse

-(NSArray*) getLeaderboards{
	if(![self._data objectForKey:@"leaderboards"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"leaderboards"]) {
		[ret addObject:[[GSLeaderboard alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListMessageDetailResponse

-(NSArray*) getMessageList{
	if(![self._data objectForKey:@"messageList"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"messageList"]) {
		[ret addObject:[[GSPlayerMessage alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListMessageResponse

		
-(NSDictionary*) getMessageList{
	return [self._data objectForKey:@"messageList"];
}
@end
@implementation GSListMessageSummaryResponse

		
-(NSDictionary*) getMessageList{
	return [self._data objectForKey:@"messageList"];
}
@end
@implementation GSListTeamChatResponse

-(NSArray*) getMessages{
	if(![self._data objectForKey:@"messages"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"messages"]) {
		[ret addObject:[[GSChatMessage alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListTeamsResponse

-(NSArray*) getTeams{
	if(![self._data objectForKey:@"teams"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"teams"]) {
		[ret addObject:[[GSTeam alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListTransactionsResponse

-(NSArray*) getTransactionList{
	if(![self._data objectForKey:@"transactionList"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"transactionList"]) {
		[ret addObject:[[GSPlayerTransaction alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSListVirtualGoodsResponse

-(NSArray*) getVirtualGoods{
	if(![self._data objectForKey:@"virtualGoods"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"virtualGoods"]) {
		[ret addObject:[[GSVirtualGood alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSLogChallengeEventResponse
@end
@implementation GSLogEventResponse
@end
@implementation GSMatchDetailsResponse

-(NSString*) getAccessToken{
	return [self._data objectForKey:@"accessToken"];
}

-(NSString*) getHost{
	return [self._data objectForKey:@"host"];
}

-(NSDictionary*) getMatchData{
	return [self._data objectForKey:@"matchData"];
}

-(NSString*) getMatchId{
	return [self._data objectForKey:@"matchId"];
}

-(NSArray*) getOpponents{
	if(![self._data objectForKey:@"opponents"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"opponents"]) {
		[ret addObject:[[GSPlayer alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSNumber*) getPeerId{
	return [self._data objectForKey:@"peerId"];
}

-(NSString*) getPlayerId{
	return [self._data objectForKey:@"playerId"];
}

-(NSNumber*) getPort{
	return [self._data objectForKey:@"port"];
}
@end
@implementation GSMatchmakingResponse
@end
@implementation GSPushRegistrationResponse

-(NSString*) getRegistrationId{
	return [self._data objectForKey:@"registrationId"];
}
@end
@implementation GSRegistrationResponse

-(NSString*) getAuthToken{
	return [self._data objectForKey:@"authToken"];
}

-(NSString*) getDisplayName{
	return [self._data objectForKey:@"displayName"];
}

-(BOOL) getNewPlayer{
	return [[self._data objectForKey:@"newPlayer"]  boolValue];
}

-(GSPlayer*) getSwitchSummary{
	if(![self._data objectForKey:@"switchSummary"]){
		return nil;
	}
	return [[GSPlayer alloc] initWithData:[self._data objectForKey:@"switchSummary"]];
}

-(NSString*) getUserId{
	return [self._data objectForKey:@"userId"];
}
@end
@implementation GSRevokePurchaseGoodsResponse

-(NSDictionary*) getRevokedGoods{
	return [self._data objectForKey:@"revokedGoods"];
}
@end
@implementation GSScheduleBulkJobAdminResponse

-(NSNumber*) getEstimatedCount{
	return [self._data objectForKey:@"estimatedCount"];
}

-(NSString*) getJobId{
	return [self._data objectForKey:@"jobId"];
}
@end
@implementation GSSendFriendMessageResponse
@end
@implementation GSSendTeamChatMessageResponse
@end
@implementation GSSocialDisconnectResponse
@end
@implementation GSSocialStatusResponse

-(NSArray*) getStatuses{
	if(![self._data objectForKey:@"statuses"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"statuses"]) {
		[ret addObject:[[GSSocialStatus alloc] initWithData:object]];
	}
	
	return ret;
}
@end
@implementation GSUpdateMessageResponse
@end
@implementation GSWithdrawChallengeResponse

-(NSString*) getChallengeInstanceId{
	return [self._data objectForKey:@"challengeInstanceId"];
}
@end

@implementation GSAchievementEarnedMessage

-(NSString*) getAchievementName{
	return [self._data objectForKey:@"achievementName"];
}

-(NSString*) getAchievementShortCode{
	return [self._data objectForKey:@"achievementShortCode"];
}

-(NSString*) getCurrency1Earned{
	return [self._data objectForKey:@"currency1Earned"];
}

-(NSString*) getCurrency2Earned{
	return [self._data objectForKey:@"currency2Earned"];
}

-(NSString*) getCurrency3Earned{
	return [self._data objectForKey:@"currency3Earned"];
}

-(NSString*) getCurrency4Earned{
	return [self._data objectForKey:@"currency4Earned"];
}

-(NSString*) getCurrency5Earned{
	return [self._data objectForKey:@"currency5Earned"];
}

-(NSString*) getCurrency6Earned{
	return [self._data objectForKey:@"currency6Earned"];
}

-(NSDictionary*) getCurrencyAwards{
	return [self._data objectForKey:@"currencyAwards"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getVirtualGoodEarned{
	return [self._data objectForKey:@"virtualGoodEarned"];
}
@end
@implementation GSChallengeAcceptedMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeChangedMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(GSLeaderboardData*) getLeaderboardData{
	if(![self._data objectForKey:@"leaderboardData"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"leaderboardData"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeChatMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeDeclinedMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeDrawnMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(GSLeaderboardData*) getLeaderboardData{
	if(![self._data objectForKey:@"leaderboardData"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"leaderboardData"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSChallengeExpiredMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSChallengeIssuedMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeJoinedMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeLapsedMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSChallengeLostMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(GSLeaderboardData*) getLeaderboardData{
	if(![self._data objectForKey:@"leaderboardData"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"leaderboardData"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWinnerName{
	return [self._data objectForKey:@"winnerName"];
}
@end
@implementation GSChallengeStartedMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSChallengeTurnTakenMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeWaitingMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSChallengeWithdrawnMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSChallengeWonMessage

-(GSChallenge*) getChallenge{
	if(![self._data objectForKey:@"challenge"]){
		return nil;
	}
	return [[GSChallenge alloc] initWithData:[self._data objectForKey:@"challenge"]];
}

-(NSNumber*) getCurrency1Won{
	return [self._data objectForKey:@"currency1Won"];
}

-(NSNumber*) getCurrency2Won{
	return [self._data objectForKey:@"currency2Won"];
}

-(NSNumber*) getCurrency3Won{
	return [self._data objectForKey:@"currency3Won"];
}

-(NSNumber*) getCurrency4Won{
	return [self._data objectForKey:@"currency4Won"];
}

-(NSNumber*) getCurrency5Won{
	return [self._data objectForKey:@"currency5Won"];
}

-(NSNumber*) getCurrency6Won{
	return [self._data objectForKey:@"currency6Won"];
}

-(NSDictionary*) getCurrencyWinnings{
	return [self._data objectForKey:@"currencyWinnings"];
}

-(GSLeaderboardData*) getLeaderboardData{
	if(![self._data objectForKey:@"leaderboardData"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"leaderboardData"]];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWinnerName{
	return [self._data objectForKey:@"winnerName"];
}
@end
@implementation GSFriendMessage

-(NSString*) getFromId{
	return [self._data objectForKey:@"fromId"];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSGlobalRankChangedMessage

-(NSNumber*) getGameId{
	return [self._data objectForKey:@"gameId"];
}

-(NSString*) getLeaderboardName{
	return [self._data objectForKey:@"leaderboardName"];
}

-(NSString*) getLeaderboardShortCode{
	return [self._data objectForKey:@"leaderboardShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(GSLeaderboardData*) getThem{
	if(![self._data objectForKey:@"them"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"them"]];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(GSLeaderboardData*) getYou{
	if(![self._data objectForKey:@"you"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"you"]];
}
@end
@implementation GSMatchFoundMessage

-(NSString*) getAccessToken{
	return [self._data objectForKey:@"accessToken"];
}

-(NSString*) getHost{
	return [self._data objectForKey:@"host"];
}

-(NSDictionary*) getMatchData{
	return [self._data objectForKey:@"matchData"];
}

-(NSString*) getMatchGroup{
	return [self._data objectForKey:@"matchGroup"];
}

-(NSString*) getMatchId{
	return [self._data objectForKey:@"matchId"];
}

-(NSString*) getMatchShortCode{
	return [self._data objectForKey:@"matchShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSArray*) getParticipants{
	if(![self._data objectForKey:@"participants"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"participants"]) {
		[ret addObject:[[GSParticipant alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSNumber*) getPort{
	return [self._data objectForKey:@"port"];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSMatchNotFoundMessage

-(NSDictionary*) getMatchData{
	return [self._data objectForKey:@"matchData"];
}

-(NSString*) getMatchGroup{
	return [self._data objectForKey:@"matchGroup"];
}

-(NSString*) getMatchShortCode{
	return [self._data objectForKey:@"matchShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSDictionary*) getParticipantData{
	return [self._data objectForKey:@"participantData"];
}

-(NSArray*) getParticipants{
	if(![self._data objectForKey:@"participants"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"participants"]) {
		[ret addObject:[[GSParticipant alloc] initWithData:object]];
	}
	
	return ret;
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSMatchUpdatedMessage

		
-(NSString*) getAddedPlayers{
	return [self._data objectForKey:@"addedPlayers"];
}

-(NSDictionary*) getMatchData{
	return [self._data objectForKey:@"matchData"];
}

-(NSString*) getMatchGroup{
	return [self._data objectForKey:@"matchGroup"];
}

-(NSString*) getMatchId{
	return [self._data objectForKey:@"matchId"];
}

-(NSString*) getMatchShortCode{
	return [self._data objectForKey:@"matchShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSArray*) getParticipants{
	if(![self._data objectForKey:@"participants"]){
		return nil;
	}
	
	NSMutableArray* ret = [[NSMutableArray alloc] init];
	
	for (id object in [self._data objectForKey:@"participants"]) {
		[ret addObject:[[GSParticipant alloc] initWithData:object]];
	}
	
	return ret;
}

		
-(NSString*) getRemovedPlayers{
	return [self._data objectForKey:@"removedPlayers"];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSNewHighScoreMessage

-(GSLeaderboardData*) getLeaderboardData{
	if(![self._data objectForKey:@"leaderboardData"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"leaderboardData"]];
}

-(NSString*) getLeaderboardName{
	return [self._data objectForKey:@"leaderboardName"];
}

-(NSString*) getLeaderboardShortCode{
	return [self._data objectForKey:@"leaderboardShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(GSLeaderboardRankDetails*) getRankDetails{
	if(![self._data objectForKey:@"rankDetails"]){
		return nil;
	}
	return [[GSLeaderboardRankDetails alloc] initWithData:[self._data objectForKey:@"rankDetails"]];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSNewTeamScoreMessage

-(GSLeaderboardData*) getLeaderboardData{
	if(![self._data objectForKey:@"leaderboardData"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"leaderboardData"]];
}

-(NSString*) getLeaderboardName{
	return [self._data objectForKey:@"leaderboardName"];
}

-(NSString*) getLeaderboardShortCode{
	return [self._data objectForKey:@"leaderboardShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(GSLeaderboardRankDetails*) getRankDetails{
	if(![self._data objectForKey:@"rankDetails"]){
		return nil;
	}
	return [[GSLeaderboardRankDetails alloc] initWithData:[self._data objectForKey:@"rankDetails"]];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSScriptMessage

-(NSDictionary*) getData{
	return [self._data objectForKey:@"data"];
}

-(NSString*) getExtCode{
	return [self._data objectForKey:@"extCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}
@end
@implementation GSSessionTerminatedMessage

-(NSString*) getAuthToken{
	return [self._data objectForKey:@"authToken"];
}
@end
@implementation GSSocialRankChangedMessage

-(NSNumber*) getGameId{
	return [self._data objectForKey:@"gameId"];
}

-(NSString*) getLeaderboardName{
	return [self._data objectForKey:@"leaderboardName"];
}

-(NSString*) getLeaderboardShortCode{
	return [self._data objectForKey:@"leaderboardShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(GSLeaderboardData*) getThem{
	if(![self._data objectForKey:@"them"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"them"]];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(GSLeaderboardData*) getYou{
	if(![self._data objectForKey:@"you"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"you"]];
}
@end
@implementation GSTeamChatMessage

-(NSString*) getChatMessageId{
	return [self._data objectForKey:@"chatMessageId"];
}

-(NSString*) getFromId{
	return [self._data objectForKey:@"fromId"];
}

-(NSString*) getMessage{
	return [self._data objectForKey:@"message"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getOwnerId{
	return [self._data objectForKey:@"ownerId"];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTeamId{
	return [self._data objectForKey:@"teamId"];
}

-(NSString*) getTeamType{
	return [self._data objectForKey:@"teamType"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSString*) getWho{
	return [self._data objectForKey:@"who"];
}
@end
@implementation GSTeamRankChangedMessage

-(NSNumber*) getGameId{
	return [self._data objectForKey:@"gameId"];
}

-(NSString*) getLeaderboardName{
	return [self._data objectForKey:@"leaderboardName"];
}

-(NSString*) getLeaderboardShortCode{
	return [self._data objectForKey:@"leaderboardShortCode"];
}

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(GSLeaderboardData*) getThem{
	if(![self._data objectForKey:@"them"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"them"]];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(GSLeaderboardData*) getYou{
	if(![self._data objectForKey:@"you"]){
		return nil;
	}
	return [[GSLeaderboardData alloc] initWithData:[self._data objectForKey:@"you"]];
}
@end
@implementation GSUploadCompleteMessage

-(NSString*) getMessageId{
	return [self._data objectForKey:@"messageId"];
}

-(BOOL) getNotification{
	return [[self._data objectForKey:@"notification"]  boolValue];
}

-(NSString*) getSubTitle{
	return [self._data objectForKey:@"subTitle"];
}

-(NSString*) getSummary{
	return [self._data objectForKey:@"summary"];
}

-(NSString*) getTitle{
	return [self._data objectForKey:@"title"];
}

-(NSDictionary*) getUploadData{
	return [self._data objectForKey:@"uploadData"];
}

-(NSString*) getUploadId{
	return [self._data objectForKey:@"uploadId"];
}
@end


@implementation GSAcceptChallengeRequest

-(id) init{
	self = [super initWithType:@".AcceptChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAcceptChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAcceptChallengeResponse* gler = [[GSAcceptChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}

@end


@implementation GSAccountDetailsRequest

-(id) init{
	self = [super initWithType:@".AccountDetailsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAccountDetailsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAccountDetailsResponse* gler = [[GSAccountDetailsResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSAmazonBuyGoodsRequest

-(id) init{
	self = [super initWithType:@".AmazonBuyGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBuyVirtualGoodResponse* gler = [[GSBuyVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAmazonUserId:(NSString*) amazonUserId{
	[self._data setObject:amazonUserId forKey:@"amazonUserId"];
}
-(void) setCurrencyCode:(NSString*) currencyCode{
	[self._data setObject:currencyCode forKey:@"currencyCode"];
}
-(void) setReceiptId:(NSString*) receiptId{
	[self._data setObject:receiptId forKey:@"receiptId"];
}

-(void) setSubUnitPrice:(NSNumber*) subUnitPrice{
	[self._data setObject:subUnitPrice forKey:@"subUnitPrice"];
}
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer{
	[self._data setObject:[NSNumber numberWithBool:uniqueTransactionByPlayer] forKey:@"uniqueTransactionByPlayer"];
}
@end


@implementation GSAmazonConnectRequest

-(id) init{
	self = [super initWithType:@".AmazonConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSAnalyticsRequest

-(id) init{
	self = [super initWithType:@".AnalyticsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAnalyticsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAnalyticsResponse* gler = [[GSAnalyticsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setData:(NSDictionary*) data{
	[self._data setObject:data forKey:@"data"];
}
-(void) setEnd:(BOOL) end{
	[self._data setObject:[NSNumber numberWithBool:end] forKey:@"end"];
}
-(void) setKey:(NSString*) key{
	[self._data setObject:key forKey:@"key"];
}

-(void) setStart:(BOOL) start{
	[self._data setObject:[NSNumber numberWithBool:start] forKey:@"start"];
}
@end


@implementation GSAroundMeLeaderboardRequest

-(id) init{
	self = [super initWithType:@".AroundMeLeaderboardRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAroundMeLeaderboardResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAroundMeLeaderboardResponse* gler = [[GSAroundMeLeaderboardResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setCustomIdFilter:(NSDictionary*) customIdFilter{
	[self._data setObject:customIdFilter forKey:@"customIdFilter"];
}
-(void) setDontErrorOnNotSocial:(BOOL) dontErrorOnNotSocial{
	[self._data setObject:[NSNumber numberWithBool:dontErrorOnNotSocial] forKey:@"dontErrorOnNotSocial"];
}
-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setFriendIds:(NSArray*) friendIds{
	[self._data setObject:friendIds forKey:@"friendIds"];
}
-(void) setIncludeFirst:(NSNumber*) includeFirst{
	[self._data setObject:includeFirst forKey:@"includeFirst"];
}
-(void) setIncludeLast:(NSNumber*) includeLast{
	[self._data setObject:includeLast forKey:@"includeLast"];
}
-(void) setInverseSocial:(BOOL) inverseSocial{
	[self._data setObject:[NSNumber numberWithBool:inverseSocial] forKey:@"inverseSocial"];
}
-(void) setLeaderboardShortCode:(NSString*) leaderboardShortCode{
	[self._data setObject:leaderboardShortCode forKey:@"leaderboardShortCode"];
}

-(void) setSocial:(BOOL) social{
	[self._data setObject:[NSNumber numberWithBool:social] forKey:@"social"];
}
-(void) setTeamIds:(NSArray*) teamIds{
	[self._data setObject:teamIds forKey:@"teamIds"];
}
-(void) setTeamTypes:(NSArray*) teamTypes{
	[self._data setObject:teamTypes forKey:@"teamTypes"];
}
@end


@implementation GSAuthenticationRequest

-(id) init{
	self = [super initWithType:@".AuthenticationRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setPassword:(NSString*) password{
	[self._data setObject:password forKey:@"password"];
}

-(void) setUserName:(NSString*) userName{
	[self._data setObject:userName forKey:@"userName"];
}
@end


@implementation GSBatchAdminRequest

-(id) init{
	self = [super initWithType:@".BatchAdminRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBatchAdminResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBatchAdminResponse* gler = [[GSBatchAdminResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setPlayerIds:(NSArray*) playerIds{
	[self._data setObject:playerIds forKey:@"playerIds"];
}
-(void) setRequest:(NSDictionary*) request{
	[self._data setObject:request forKey:@"request"];
}

@end


@implementation GSBuyVirtualGoodsRequest

-(id) init{
	self = [super initWithType:@".BuyVirtualGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBuyVirtualGoodResponse* gler = [[GSBuyVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setCurrencyShortCode:(NSString*) currencyShortCode{
	[self._data setObject:currencyShortCode forKey:@"currencyShortCode"];
}
-(void) setCurrencyType:(NSNumber*) currencyType{
	[self._data setObject:currencyType forKey:@"currencyType"];
}
-(void) setQuantity:(NSNumber*) quantity{
	[self._data setObject:quantity forKey:@"quantity"];
}

-(void) setShortCode:(NSString*) shortCode{
	[self._data setObject:shortCode forKey:@"shortCode"];
}
@end


@implementation GSCancelBulkJobAdminRequest

-(id) init{
	self = [super initWithType:@".CancelBulkJobAdminRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSCancelBulkJobAdminResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSCancelBulkJobAdminResponse* gler = [[GSCancelBulkJobAdminResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setBulkJobIds:(NSArray*) bulkJobIds{
	[self._data setObject:bulkJobIds forKey:@"bulkJobIds"];
}

@end


@implementation GSChangeUserDetailsRequest

-(id) init{
	self = [super initWithType:@".ChangeUserDetailsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSChangeUserDetailsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSChangeUserDetailsResponse* gler = [[GSChangeUserDetailsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDisplayName:(NSString*) displayName{
	[self._data setObject:displayName forKey:@"displayName"];
}
-(void) setLanguage:(NSString*) language{
	[self._data setObject:language forKey:@"language"];
}
-(void) setNewPassword:(NSString*) newPassword{
	[self._data setObject:newPassword forKey:@"newPassword"];
}
-(void) setOldPassword:(NSString*) oldPassword{
	[self._data setObject:oldPassword forKey:@"oldPassword"];
}

-(void) setUserName:(NSString*) userName{
	[self._data setObject:userName forKey:@"userName"];
}
@end


@implementation GSChatOnChallengeRequest

-(id) init{
	self = [super initWithType:@".ChatOnChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSChatOnChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSChatOnChallengeResponse* gler = [[GSChatOnChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}

@end


@implementation GSConsumeVirtualGoodRequest

-(id) init{
	self = [super initWithType:@".ConsumeVirtualGoodRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSConsumeVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSConsumeVirtualGoodResponse* gler = [[GSConsumeVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setQuantity:(NSNumber*) quantity{
	[self._data setObject:quantity forKey:@"quantity"];
}

-(void) setShortCode:(NSString*) shortCode{
	[self._data setObject:shortCode forKey:@"shortCode"];
}
@end


@implementation GSCreateChallengeRequest

-(id) init{
	self = [super initWithType:@".CreateChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSCreateChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSCreateChallengeResponse* gler = [[GSCreateChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessType:(NSString*) accessType{
	[self._data setObject:accessType forKey:@"accessType"];
}
-(void) setAutoStartJoinedChallengeOnMaxPlayers:(BOOL) autoStartJoinedChallengeOnMaxPlayers{
	[self._data setObject:[NSNumber numberWithBool:autoStartJoinedChallengeOnMaxPlayers] forKey:@"autoStartJoinedChallengeOnMaxPlayers"];
}
-(void) setChallengeMessage:(NSString*) challengeMessage{
	[self._data setObject:challengeMessage forKey:@"challengeMessage"];
}
-(void) setChallengeShortCode:(NSString*) challengeShortCode{
	[self._data setObject:challengeShortCode forKey:@"challengeShortCode"];
}
-(void) setCurrency1Wager:(NSNumber*) currency1Wager{
	[self._data setObject:currency1Wager forKey:@"currency1Wager"];
}
-(void) setCurrency2Wager:(NSNumber*) currency2Wager{
	[self._data setObject:currency2Wager forKey:@"currency2Wager"];
}
-(void) setCurrency3Wager:(NSNumber*) currency3Wager{
	[self._data setObject:currency3Wager forKey:@"currency3Wager"];
}
-(void) setCurrency4Wager:(NSNumber*) currency4Wager{
	[self._data setObject:currency4Wager forKey:@"currency4Wager"];
}
-(void) setCurrency5Wager:(NSNumber*) currency5Wager{
	[self._data setObject:currency5Wager forKey:@"currency5Wager"];
}
-(void) setCurrency6Wager:(NSNumber*) currency6Wager{
	[self._data setObject:currency6Wager forKey:@"currency6Wager"];
}
-(void) setCurrencyWagers:(NSDictionary*) currencyWagers{
	[self._data setObject:currencyWagers forKey:@"currencyWagers"];
}
-(void) setEligibilityCriteria:(NSDictionary*) eligibilityCriteria{
	[self._data setObject:eligibilityCriteria forKey:@"eligibilityCriteria"];
}
-(void) setEndTime:(NSDate*) endTime{
	[self._data setObject:[self getStringFromDate:endTime] forKey:@"endTime"];
}
-(void) setExpiryTime:(NSDate*) expiryTime{
	[self._data setObject:[self getStringFromDate:expiryTime] forKey:@"expiryTime"];
}
-(void) setMaxAttempts:(NSNumber*) maxAttempts{
	[self._data setObject:maxAttempts forKey:@"maxAttempts"];
}
-(void) setMaxPlayers:(NSNumber*) maxPlayers{
	[self._data setObject:maxPlayers forKey:@"maxPlayers"];
}
-(void) setMinPlayers:(NSNumber*) minPlayers{
	[self._data setObject:minPlayers forKey:@"minPlayers"];
}

-(void) setSilent:(BOOL) silent{
	[self._data setObject:[NSNumber numberWithBool:silent] forKey:@"silent"];
}
-(void) setStartTime:(NSDate*) startTime{
	[self._data setObject:[self getStringFromDate:startTime] forKey:@"startTime"];
}
-(void) setUsersToChallenge:(NSArray*) usersToChallenge{
	[self._data setObject:usersToChallenge forKey:@"usersToChallenge"];
}
@end


@implementation GSCreateTeamRequest

-(id) init{
	self = [super initWithType:@".CreateTeamRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSCreateTeamResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSCreateTeamResponse* gler = [[GSCreateTeamResponse alloc] initWithData:response];
        callback(gler);
    };
}


-(void) setTeamId:(NSString*) teamId{
	[self._data setObject:teamId forKey:@"teamId"];
}
-(void) setTeamName:(NSString*) teamName{
	[self._data setObject:teamName forKey:@"teamName"];
}
-(void) setTeamType:(NSString*) teamType{
	[self._data setObject:teamType forKey:@"teamType"];
}
@end


@implementation GSDeclineChallengeRequest

-(id) init{
	self = [super initWithType:@".DeclineChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSDeclineChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSDeclineChallengeResponse* gler = [[GSDeclineChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}

@end


@implementation GSDeviceAuthenticationRequest

-(id) init{
	self = [super initWithType:@".DeviceAuthenticationRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDeviceId:(NSString*) deviceId{
	[self._data setObject:deviceId forKey:@"deviceId"];
}
-(void) setDeviceModel:(NSString*) deviceModel{
	[self._data setObject:deviceModel forKey:@"deviceModel"];
}
-(void) setDeviceName:(NSString*) deviceName{
	[self._data setObject:deviceName forKey:@"deviceName"];
}
-(void) setDeviceOS:(NSString*) deviceOS{
	[self._data setObject:deviceOS forKey:@"deviceOS"];
}
-(void) setDeviceType:(NSString*) deviceType{
	[self._data setObject:deviceType forKey:@"deviceType"];
}
-(void) setDisplayName:(NSString*) displayName{
	[self._data setObject:displayName forKey:@"displayName"];
}
-(void) setOperatingSystem:(NSString*) operatingSystem{
	[self._data setObject:operatingSystem forKey:@"operatingSystem"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
@end


@implementation GSDismissMessageRequest

-(id) init{
	self = [super initWithType:@".DismissMessageRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSDismissMessageResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSDismissMessageResponse* gler = [[GSDismissMessageResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMessageId:(NSString*) messageId{
	[self._data setObject:messageId forKey:@"messageId"];
}

@end


@implementation GSDismissMultipleMessagesRequest

-(id) init{
	self = [super initWithType:@".DismissMultipleMessagesRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSDismissMultipleMessagesResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSDismissMultipleMessagesResponse* gler = [[GSDismissMultipleMessagesResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMessageIds:(NSArray*) messageIds{
	[self._data setObject:messageIds forKey:@"messageIds"];
}

@end


@implementation GSDropTeamRequest

-(id) init{
	self = [super initWithType:@".DropTeamRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSDropTeamResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSDropTeamResponse* gler = [[GSDropTeamResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setOwnerId:(NSString*) ownerId{
	[self._data setObject:ownerId forKey:@"ownerId"];
}

-(void) setTeamId:(NSString*) teamId{
	[self._data setObject:teamId forKey:@"teamId"];
}
-(void) setTeamType:(NSString*) teamType{
	[self._data setObject:teamType forKey:@"teamType"];
}
@end


@implementation GSEndSessionRequest

-(id) init{
	self = [super initWithType:@".EndSessionRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSEndSessionResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSEndSessionResponse* gler = [[GSEndSessionResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSFacebookConnectRequest

-(id) init{
	self = [super initWithType:@".FacebookConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setCode:(NSString*) code{
	[self._data setObject:code forKey:@"code"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSFindChallengeRequest

-(id) init{
	self = [super initWithType:@".FindChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSFindChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSFindChallengeResponse* gler = [[GSFindChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessType:(NSString*) accessType{
	[self._data setObject:accessType forKey:@"accessType"];
}
-(void) setCount:(NSNumber*) count{
	[self._data setObject:count forKey:@"count"];
}
-(void) setEligibility:(NSDictionary*) eligibility{
	[self._data setObject:eligibility forKey:@"eligibility"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

-(void) setShortCode:(NSArray*) shortCode{
	[self._data setObject:shortCode forKey:@"shortCode"];
}
@end


@implementation GSFindMatchRequest

-(id) init{
	self = [super initWithType:@".FindMatchRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSFindMatchResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSFindMatchResponse* gler = [[GSFindMatchResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAction:(NSString*) action{
	[self._data setObject:action forKey:@"action"];
}
-(void) setMatchGroup:(NSString*) matchGroup{
	[self._data setObject:matchGroup forKey:@"matchGroup"];
}
-(void) setMatchShortCode:(NSString*) matchShortCode{
	[self._data setObject:matchShortCode forKey:@"matchShortCode"];
}

-(void) setSkill:(NSNumber*) skill{
	[self._data setObject:skill forKey:@"skill"];
}
@end


@implementation GSFindPendingMatchesRequest

-(id) init{
	self = [super initWithType:@".FindPendingMatchesRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSFindPendingMatchesResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSFindPendingMatchesResponse* gler = [[GSFindPendingMatchesResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMatchGroup:(NSString*) matchGroup{
	[self._data setObject:matchGroup forKey:@"matchGroup"];
}
-(void) setMatchShortCode:(NSString*) matchShortCode{
	[self._data setObject:matchShortCode forKey:@"matchShortCode"];
}
-(void) setMaxMatchesToFind:(NSNumber*) maxMatchesToFind{
	[self._data setObject:maxMatchesToFind forKey:@"maxMatchesToFind"];
}

@end


@implementation GSGameCenterConnectRequest

-(id) init{
	self = [super initWithType:@".GameCenterConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDisplayName:(NSString*) displayName{
	[self._data setObject:displayName forKey:@"displayName"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}
-(void) setExternalPlayerId:(NSString*) externalPlayerId{
	[self._data setObject:externalPlayerId forKey:@"externalPlayerId"];
}
-(void) setPublicKeyUrl:(NSString*) publicKeyUrl{
	[self._data setObject:publicKeyUrl forKey:@"publicKeyUrl"];
}

-(void) setSalt:(NSString*) salt{
	[self._data setObject:salt forKey:@"salt"];
}
-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSignature:(NSString*) signature{
	[self._data setObject:signature forKey:@"signature"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
-(void) setTimestamp:(NSNumber*) timestamp{
	[self._data setObject:timestamp forKey:@"timestamp"];
}
@end


@implementation GSGetChallengeRequest

-(id) init{
	self = [super initWithType:@".GetChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetChallengeResponse* gler = [[GSGetChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}

@end


@implementation GSGetDownloadableRequest

-(id) init{
	self = [super initWithType:@".GetDownloadableRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetDownloadableResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetDownloadableResponse* gler = [[GSGetDownloadableResponse alloc] initWithData:response];
        callback(gler);
    };
}


-(void) setShortCode:(NSString*) shortCode{
	[self._data setObject:shortCode forKey:@"shortCode"];
}
@end


@implementation GSGetLeaderboardEntriesRequest

-(id) init{
	self = [super initWithType:@".GetLeaderboardEntriesRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetLeaderboardEntriesResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetLeaderboardEntriesResponse* gler = [[GSGetLeaderboardEntriesResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallenges:(NSArray*) challenges{
	[self._data setObject:challenges forKey:@"challenges"];
}
-(void) setInverseSocial:(BOOL) inverseSocial{
	[self._data setObject:[NSNumber numberWithBool:inverseSocial] forKey:@"inverseSocial"];
}
-(void) setLeaderboards:(NSArray*) leaderboards{
	[self._data setObject:leaderboards forKey:@"leaderboards"];
}
-(void) setPlayer:(NSString*) player{
	[self._data setObject:player forKey:@"player"];
}

-(void) setSocial:(BOOL) social{
	[self._data setObject:[NSNumber numberWithBool:social] forKey:@"social"];
}
-(void) setTeamTypes:(NSArray*) teamTypes{
	[self._data setObject:teamTypes forKey:@"teamTypes"];
}
@end


@implementation GSGetMessageRequest

-(id) init{
	self = [super initWithType:@".GetMessageRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetMessageResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetMessageResponse* gler = [[GSGetMessageResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMessageId:(NSString*) messageId{
	[self._data setObject:messageId forKey:@"messageId"];
}

@end


@implementation GSGetMyTeamsRequest

-(id) init{
	self = [super initWithType:@".GetMyTeamsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetMyTeamsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetMyTeamsResponse* gler = [[GSGetMyTeamsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setOwnedOnly:(BOOL) ownedOnly{
	[self._data setObject:[NSNumber numberWithBool:ownedOnly] forKey:@"ownedOnly"];
}

-(void) setTeamTypes:(NSArray*) teamTypes{
	[self._data setObject:teamTypes forKey:@"teamTypes"];
}
@end


@implementation GSGetPropertyRequest

-(id) init{
	self = [super initWithType:@".GetPropertyRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetPropertyResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetPropertyResponse* gler = [[GSGetPropertyResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setPropertyShortCode:(NSString*) propertyShortCode{
	[self._data setObject:propertyShortCode forKey:@"propertyShortCode"];
}

@end


@implementation GSGetPropertySetRequest

-(id) init{
	self = [super initWithType:@".GetPropertySetRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetPropertySetResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetPropertySetResponse* gler = [[GSGetPropertySetResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setPropertySetShortCode:(NSString*) propertySetShortCode{
	[self._data setObject:propertySetShortCode forKey:@"propertySetShortCode"];
}

@end


@implementation GSGetTeamRequest

-(id) init{
	self = [super initWithType:@".GetTeamRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetTeamResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetTeamResponse* gler = [[GSGetTeamResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setOwnerId:(NSString*) ownerId{
	[self._data setObject:ownerId forKey:@"ownerId"];
}

-(void) setTeamId:(NSString*) teamId{
	[self._data setObject:teamId forKey:@"teamId"];
}
-(void) setTeamType:(NSString*) teamType{
	[self._data setObject:teamType forKey:@"teamType"];
}
@end


@implementation GSGetUploadUrlRequest

-(id) init{
	self = [super initWithType:@".GetUploadUrlRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetUploadUrlResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetUploadUrlResponse* gler = [[GSGetUploadUrlResponse alloc] initWithData:response];
        callback(gler);
    };
}


-(void) setUploadData:(NSDictionary*) uploadData{
	[self._data setObject:uploadData forKey:@"uploadData"];
}
@end


@implementation GSGetUploadedRequest

-(id) init{
	self = [super initWithType:@".GetUploadedRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSGetUploadedResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSGetUploadedResponse* gler = [[GSGetUploadedResponse alloc] initWithData:response];
        callback(gler);
    };
}


-(void) setUploadId:(NSString*) uploadId{
	[self._data setObject:uploadId forKey:@"uploadId"];
}
@end


@implementation GSGooglePlayBuyGoodsRequest

-(id) init{
	self = [super initWithType:@".GooglePlayBuyGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBuyVirtualGoodResponse* gler = [[GSBuyVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setCurrencyCode:(NSString*) currencyCode{
	[self._data setObject:currencyCode forKey:@"currencyCode"];
}

-(void) setSignature:(NSString*) signature{
	[self._data setObject:signature forKey:@"signature"];
}
-(void) setSignedData:(NSString*) signedData{
	[self._data setObject:signedData forKey:@"signedData"];
}
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice{
	[self._data setObject:subUnitPrice forKey:@"subUnitPrice"];
}
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer{
	[self._data setObject:[NSNumber numberWithBool:uniqueTransactionByPlayer] forKey:@"uniqueTransactionByPlayer"];
}
@end


@implementation GSGooglePlayConnectRequest

-(id) init{
	self = [super initWithType:@".GooglePlayConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setCode:(NSString*) code{
	[self._data setObject:code forKey:@"code"];
}
-(void) setDisplayName:(NSString*) displayName{
	[self._data setObject:displayName forKey:@"displayName"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}
-(void) setGooglePlusScope:(BOOL) googlePlusScope{
	[self._data setObject:[NSNumber numberWithBool:googlePlusScope] forKey:@"googlePlusScope"];
}
-(void) setProfileScope:(BOOL) profileScope{
	[self._data setObject:[NSNumber numberWithBool:profileScope] forKey:@"profileScope"];
}
-(void) setRedirectUri:(NSString*) redirectUri{
	[self._data setObject:redirectUri forKey:@"redirectUri"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSGooglePlusConnectRequest

-(id) init{
	self = [super initWithType:@".GooglePlusConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setCode:(NSString*) code{
	[self._data setObject:code forKey:@"code"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}
-(void) setRedirectUri:(NSString*) redirectUri{
	[self._data setObject:redirectUri forKey:@"redirectUri"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSIOSBuyGoodsRequest

-(id) init{
	self = [super initWithType:@".IOSBuyGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBuyVirtualGoodResponse* gler = [[GSBuyVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setCurrencyCode:(NSString*) currencyCode{
	[self._data setObject:currencyCode forKey:@"currencyCode"];
}
-(void) setReceipt:(NSString*) receipt{
	[self._data setObject:receipt forKey:@"receipt"];
}

-(void) setSandbox:(BOOL) sandbox{
	[self._data setObject:[NSNumber numberWithBool:sandbox] forKey:@"sandbox"];
}
-(void) setSubUnitPrice:(NSNumber*) subUnitPrice{
	[self._data setObject:subUnitPrice forKey:@"subUnitPrice"];
}
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer{
	[self._data setObject:[NSNumber numberWithBool:uniqueTransactionByPlayer] forKey:@"uniqueTransactionByPlayer"];
}
@end


@implementation GSJoinChallengeRequest

-(id) init{
	self = [super initWithType:@".JoinChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSJoinChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSJoinChallengeResponse* gler = [[GSJoinChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setEligibility:(NSDictionary*) eligibility{
	[self._data setObject:eligibility forKey:@"eligibility"];
}
-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}

@end


@implementation GSJoinPendingMatchRequest

-(id) init{
	self = [super initWithType:@".JoinPendingMatchRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSJoinPendingMatchResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSJoinPendingMatchResponse* gler = [[GSJoinPendingMatchResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMatchGroup:(NSString*) matchGroup{
	[self._data setObject:matchGroup forKey:@"matchGroup"];
}
-(void) setMatchShortCode:(NSString*) matchShortCode{
	[self._data setObject:matchShortCode forKey:@"matchShortCode"];
}
-(void) setPendingMatchId:(NSString*) pendingMatchId{
	[self._data setObject:pendingMatchId forKey:@"pendingMatchId"];
}

@end


@implementation GSJoinTeamRequest

-(id) init{
	self = [super initWithType:@".JoinTeamRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSJoinTeamResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSJoinTeamResponse* gler = [[GSJoinTeamResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setOwnerId:(NSString*) ownerId{
	[self._data setObject:ownerId forKey:@"ownerId"];
}

-(void) setTeamId:(NSString*) teamId{
	[self._data setObject:teamId forKey:@"teamId"];
}
-(void) setTeamType:(NSString*) teamType{
	[self._data setObject:teamType forKey:@"teamType"];
}
@end


@implementation GSKongregateConnectRequest

-(id) init{
	self = [super initWithType:@".KongregateConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}
-(void) setGameAuthToken:(NSString*) gameAuthToken{
	[self._data setObject:gameAuthToken forKey:@"gameAuthToken"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
-(void) setUserId:(NSString*) userId{
	[self._data setObject:userId forKey:@"userId"];
}
@end


@implementation GSLeaderboardDataRequest

-(id) init{
	self = [super initWithType:@".LeaderboardDataRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSLeaderboardDataResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSLeaderboardDataResponse* gler = [[GSLeaderboardDataResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setDontErrorOnNotSocial:(BOOL) dontErrorOnNotSocial{
	[self._data setObject:[NSNumber numberWithBool:dontErrorOnNotSocial] forKey:@"dontErrorOnNotSocial"];
}
-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setFriendIds:(NSArray*) friendIds{
	[self._data setObject:friendIds forKey:@"friendIds"];
}
-(void) setIncludeFirst:(NSNumber*) includeFirst{
	[self._data setObject:includeFirst forKey:@"includeFirst"];
}
-(void) setIncludeLast:(NSNumber*) includeLast{
	[self._data setObject:includeLast forKey:@"includeLast"];
}
-(void) setInverseSocial:(BOOL) inverseSocial{
	[self._data setObject:[NSNumber numberWithBool:inverseSocial] forKey:@"inverseSocial"];
}
-(void) setLeaderboardShortCode:(NSString*) leaderboardShortCode{
	[self._data setObject:leaderboardShortCode forKey:@"leaderboardShortCode"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

-(void) setSocial:(BOOL) social{
	[self._data setObject:[NSNumber numberWithBool:social] forKey:@"social"];
}
-(void) setTeamIds:(NSArray*) teamIds{
	[self._data setObject:teamIds forKey:@"teamIds"];
}
-(void) setTeamTypes:(NSArray*) teamTypes{
	[self._data setObject:teamTypes forKey:@"teamTypes"];
}
@end


@implementation GSLeaderboardsEntriesRequest

-(id) init{
	self = [super initWithType:@".LeaderboardsEntriesRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSLeaderboardsEntriesResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSLeaderboardsEntriesResponse* gler = [[GSLeaderboardsEntriesResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallenges:(NSArray*) challenges{
	[self._data setObject:challenges forKey:@"challenges"];
}
-(void) setInverseSocial:(BOOL) inverseSocial{
	[self._data setObject:[NSNumber numberWithBool:inverseSocial] forKey:@"inverseSocial"];
}
-(void) setLeaderboards:(NSArray*) leaderboards{
	[self._data setObject:leaderboards forKey:@"leaderboards"];
}
-(void) setPlayer:(NSString*) player{
	[self._data setObject:player forKey:@"player"];
}

-(void) setSocial:(BOOL) social{
	[self._data setObject:[NSNumber numberWithBool:social] forKey:@"social"];
}
-(void) setTeamTypes:(NSArray*) teamTypes{
	[self._data setObject:teamTypes forKey:@"teamTypes"];
}
@end


@implementation GSLeaveTeamRequest

-(id) init{
	self = [super initWithType:@".LeaveTeamRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSLeaveTeamResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSLeaveTeamResponse* gler = [[GSLeaveTeamResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setOwnerId:(NSString*) ownerId{
	[self._data setObject:ownerId forKey:@"ownerId"];
}

-(void) setTeamId:(NSString*) teamId{
	[self._data setObject:teamId forKey:@"teamId"];
}
-(void) setTeamType:(NSString*) teamType{
	[self._data setObject:teamType forKey:@"teamType"];
}
@end


@implementation GSListAchievementsRequest

-(id) init{
	self = [super initWithType:@".ListAchievementsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListAchievementsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListAchievementsResponse* gler = [[GSListAchievementsResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSListBulkJobsAdminRequest

-(id) init{
	self = [super initWithType:@".ListBulkJobsAdminRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListBulkJobsAdminResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListBulkJobsAdminResponse* gler = [[GSListBulkJobsAdminResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setBulkJobIds:(NSArray*) bulkJobIds{
	[self._data setObject:bulkJobIds forKey:@"bulkJobIds"];
}

@end


@implementation GSListChallengeRequest

-(id) init{
	self = [super initWithType:@".ListChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListChallengeResponse* gler = [[GSListChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

-(void) setShortCode:(NSString*) shortCode{
	[self._data setObject:shortCode forKey:@"shortCode"];
}
-(void) setState:(NSString*) state{
	[self._data setObject:state forKey:@"state"];
}
-(void) setStates:(NSArray*) states{
	[self._data setObject:states forKey:@"states"];
}
@end


@implementation GSListChallengeTypeRequest

-(id) init{
	self = [super initWithType:@".ListChallengeTypeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListChallengeTypeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListChallengeTypeResponse* gler = [[GSListChallengeTypeResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSListGameFriendsRequest

-(id) init{
	self = [super initWithType:@".ListGameFriendsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListGameFriendsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListGameFriendsResponse* gler = [[GSListGameFriendsResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSListInviteFriendsRequest

-(id) init{
	self = [super initWithType:@".ListInviteFriendsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListInviteFriendsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListInviteFriendsResponse* gler = [[GSListInviteFriendsResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSListLeaderboardsRequest

-(id) init{
	self = [super initWithType:@".ListLeaderboardsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListLeaderboardsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListLeaderboardsResponse* gler = [[GSListLeaderboardsResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSListMessageDetailRequest

-(id) init{
	self = [super initWithType:@".ListMessageDetailRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListMessageDetailResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListMessageDetailResponse* gler = [[GSListMessageDetailResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setInclude:(NSString*) include{
	[self._data setObject:include forKey:@"include"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

-(void) setStatus:(NSString*) status{
	[self._data setObject:status forKey:@"status"];
}
@end


@implementation GSListMessageRequest

-(id) init{
	self = [super initWithType:@".ListMessageRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListMessageResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListMessageResponse* gler = [[GSListMessageResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setInclude:(NSString*) include{
	[self._data setObject:include forKey:@"include"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

@end


@implementation GSListMessageSummaryRequest

-(id) init{
	self = [super initWithType:@".ListMessageSummaryRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListMessageSummaryResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListMessageSummaryResponse* gler = [[GSListMessageSummaryResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

@end


@implementation GSListTeamChatRequest

-(id) init{
	self = [super initWithType:@".ListTeamChatRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListTeamChatResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListTeamChatResponse* gler = [[GSListTeamChatResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}
-(void) setOwnerId:(NSString*) ownerId{
	[self._data setObject:ownerId forKey:@"ownerId"];
}

-(void) setTeamId:(NSString*) teamId{
	[self._data setObject:teamId forKey:@"teamId"];
}
-(void) setTeamType:(NSString*) teamType{
	[self._data setObject:teamType forKey:@"teamType"];
}
@end


@implementation GSListTeamsRequest

-(id) init{
	self = [super initWithType:@".ListTeamsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListTeamsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListTeamsResponse* gler = [[GSListTeamsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

-(void) setTeamNameFilter:(NSString*) teamNameFilter{
	[self._data setObject:teamNameFilter forKey:@"teamNameFilter"];
}
-(void) setTeamTypeFilter:(NSString*) teamTypeFilter{
	[self._data setObject:teamTypeFilter forKey:@"teamTypeFilter"];
}
@end


@implementation GSListTransactionsRequest

-(id) init{
	self = [super initWithType:@".ListTransactionsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListTransactionsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListTransactionsResponse* gler = [[GSListTransactionsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDateFrom:(NSDate*) dateFrom{
	[self._data setObject:[self getStringFromDate:dateFrom] forKey:@"dateFrom"];
}
-(void) setDateTo:(NSDate*) dateTo{
	[self._data setObject:[self getStringFromDate:dateTo] forKey:@"dateTo"];
}
-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setInclude:(NSString*) include{
	[self._data setObject:include forKey:@"include"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

@end


@implementation GSListVirtualGoodsRequest

-(id) init{
	self = [super initWithType:@".ListVirtualGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSListVirtualGoodsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSListVirtualGoodsResponse* gler = [[GSListVirtualGoodsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setIncludeDisabled:(BOOL) includeDisabled{
	[self._data setObject:[NSNumber numberWithBool:includeDisabled] forKey:@"includeDisabled"];
}

-(void) setTags:(NSArray*) tags{
	[self._data setObject:tags forKey:@"tags"];
}
@end


@implementation GSLogChallengeEventRequest

-(id) init{
	self = [super initWithType:@".LogChallengeEventRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSLogChallengeEventResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSLogChallengeEventResponse* gler = [[GSLogChallengeEventResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setEventKey:(NSString*) eventKey{
	[self._data setObject:eventKey forKey:@"eventKey"];
}

-(void) setEventAttribute:(NSString*)shortCode withNumber:(NSNumber*) value{
	[self._data setObject:value forKey:shortCode];
}
-(void) setEventAttribute:(NSString*)shortCode withString:(NSString*) value{
	[self._data setObject:value forKey:shortCode];
}
-(void) setEventAttribute:(NSString*)shortCode withDictionary:(NSDictionary*) value{
	[self._data setObject:value forKey:shortCode];
}
@end


@implementation GSLogEventRequest

-(id) init{
	self = [super initWithType:@".LogEventRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSLogEventResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSLogEventResponse* gler = [[GSLogEventResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setEventKey:(NSString*) eventKey{
	[self._data setObject:eventKey forKey:@"eventKey"];
}

-(void) setEventAttribute:(NSString*)shortCode withNumber:(NSNumber*) value{
	[self._data setObject:value forKey:shortCode];
}
-(void) setEventAttribute:(NSString*)shortCode withString:(NSString*) value{
	[self._data setObject:value forKey:shortCode];
}
-(void) setEventAttribute:(NSString*)shortCode withDictionary:(NSDictionary*) value{
	[self._data setObject:value forKey:shortCode];
}
@end


@implementation GSMatchDetailsRequest

-(id) init{
	self = [super initWithType:@".MatchDetailsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSMatchDetailsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSMatchDetailsResponse* gler = [[GSMatchDetailsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMatchId:(NSString*) matchId{
	[self._data setObject:matchId forKey:@"matchId"];
}
-(void) setRealtimeEnabled:(BOOL) realtimeEnabled{
	[self._data setObject:[NSNumber numberWithBool:realtimeEnabled] forKey:@"realtimeEnabled"];
}

@end


@implementation GSMatchmakingRequest

-(id) init{
	self = [super initWithType:@".MatchmakingRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSMatchmakingResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSMatchmakingResponse* gler = [[GSMatchmakingResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAction:(NSString*) action{
	[self._data setObject:action forKey:@"action"];
}
-(void) setCustomQuery:(NSDictionary*) customQuery{
	[self._data setObject:customQuery forKey:@"customQuery"];
}
-(void) setMatchData:(NSDictionary*) matchData{
	[self._data setObject:matchData forKey:@"matchData"];
}
-(void) setMatchGroup:(NSString*) matchGroup{
	[self._data setObject:matchGroup forKey:@"matchGroup"];
}
-(void) setMatchShortCode:(NSString*) matchShortCode{
	[self._data setObject:matchShortCode forKey:@"matchShortCode"];
}
-(void) setParticipantData:(NSDictionary*) participantData{
	[self._data setObject:participantData forKey:@"participantData"];
}

-(void) setSkill:(NSNumber*) skill{
	[self._data setObject:skill forKey:@"skill"];
}
@end


@implementation GSNXConnectRequest

-(id) init{
	self = [super initWithType:@".NXConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccountPerLoginId:(BOOL) accountPerLoginId{
	[self._data setObject:[NSNumber numberWithBool:accountPerLoginId] forKey:@"accountPerLoginId"];
}
-(void) setDisplayName:(NSString*) displayName{
	[self._data setObject:displayName forKey:@"displayName"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}
-(void) setNsaIdToken:(NSString*) nsaIdToken{
	[self._data setObject:nsaIdToken forKey:@"nsaIdToken"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSPSNConnectRequest

-(id) init{
	self = [super initWithType:@".PSNConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAuthorizationCode:(NSString*) authorizationCode{
	[self._data setObject:authorizationCode forKey:@"authorizationCode"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}
-(void) setRedirectUri:(NSString*) redirectUri{
	[self._data setObject:redirectUri forKey:@"redirectUri"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSPsnBuyGoodsRequest

-(id) init{
	self = [super initWithType:@".PsnBuyGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBuyVirtualGoodResponse* gler = [[GSBuyVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAuthorizationCode:(NSString*) authorizationCode{
	[self._data setObject:authorizationCode forKey:@"authorizationCode"];
}
-(void) setCurrencyCode:(NSString*) currencyCode{
	[self._data setObject:currencyCode forKey:@"currencyCode"];
}
-(void) setEntitlementLabel:(NSString*) entitlementLabel{
	[self._data setObject:entitlementLabel forKey:@"entitlementLabel"];
}
-(void) setRedirectUri:(NSString*) redirectUri{
	[self._data setObject:redirectUri forKey:@"redirectUri"];
}

-(void) setSubUnitPrice:(NSNumber*) subUnitPrice{
	[self._data setObject:subUnitPrice forKey:@"subUnitPrice"];
}
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer{
	[self._data setObject:[NSNumber numberWithBool:uniqueTransactionByPlayer] forKey:@"uniqueTransactionByPlayer"];
}
-(void) setUseCount:(NSNumber*) useCount{
	[self._data setObject:useCount forKey:@"useCount"];
}
@end


@implementation GSPushRegistrationRequest

-(id) init{
	self = [super initWithType:@".PushRegistrationRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSPushRegistrationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSPushRegistrationResponse* gler = [[GSPushRegistrationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDeviceOS:(NSString*) deviceOS{
	[self._data setObject:deviceOS forKey:@"deviceOS"];
}
-(void) setPushId:(NSString*) pushId{
	[self._data setObject:pushId forKey:@"pushId"];
}

@end


@implementation GSQQConnectRequest

-(id) init{
	self = [super initWithType:@".QQConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSRegistrationRequest

-(id) init{
	self = [super initWithType:@".RegistrationRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSRegistrationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSRegistrationResponse* gler = [[GSRegistrationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDisplayName:(NSString*) displayName{
	[self._data setObject:displayName forKey:@"displayName"];
}
-(void) setPassword:(NSString*) password{
	[self._data setObject:password forKey:@"password"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setUserName:(NSString*) userName{
	[self._data setObject:userName forKey:@"userName"];
}
@end


@implementation GSRevokePurchaseGoodsRequest

-(id) init{
	self = [super initWithType:@".RevokePurchaseGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSRevokePurchaseGoodsResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSRevokePurchaseGoodsResponse* gler = [[GSRevokePurchaseGoodsResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setPlayerId:(NSString*) playerId{
	[self._data setObject:playerId forKey:@"playerId"];
}

-(void) setStoreType:(NSString*) storeType{
	[self._data setObject:storeType forKey:@"storeType"];
}
-(void) setTransactionIds:(NSArray*) transactionIds{
	[self._data setObject:transactionIds forKey:@"transactionIds"];
}
@end


@implementation GSScheduleBulkJobAdminRequest

-(id) init{
	self = [super initWithType:@".ScheduleBulkJobAdminRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSScheduleBulkJobAdminResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSScheduleBulkJobAdminResponse* gler = [[GSScheduleBulkJobAdminResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setData:(NSDictionary*) data{
	[self._data setObject:data forKey:@"data"];
}
-(void) setModuleShortCode:(NSString*) moduleShortCode{
	[self._data setObject:moduleShortCode forKey:@"moduleShortCode"];
}
-(void) setPlayerQuery:(NSDictionary*) playerQuery{
	[self._data setObject:playerQuery forKey:@"playerQuery"];
}

-(void) setScheduledTime:(NSDate*) scheduledTime{
	[self._data setObject:[self getStringFromDate:scheduledTime] forKey:@"scheduledTime"];
}
-(void) setScript:(NSString*) script{
	[self._data setObject:script forKey:@"script"];
}
@end


@implementation GSSendFriendMessageRequest

-(id) init{
	self = [super initWithType:@".SendFriendMessageRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSSendFriendMessageResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSSendFriendMessageResponse* gler = [[GSSendFriendMessageResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setFriendIds:(NSArray*) friendIds{
	[self._data setObject:friendIds forKey:@"friendIds"];
}
-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}

@end


@implementation GSSendTeamChatMessageRequest

-(id) init{
	self = [super initWithType:@".SendTeamChatMessageRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSSendTeamChatMessageResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSSendTeamChatMessageResponse* gler = [[GSSendTeamChatMessageResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}
-(void) setOwnerId:(NSString*) ownerId{
	[self._data setObject:ownerId forKey:@"ownerId"];
}

-(void) setTeamId:(NSString*) teamId{
	[self._data setObject:teamId forKey:@"teamId"];
}
-(void) setTeamType:(NSString*) teamType{
	[self._data setObject:teamType forKey:@"teamType"];
}
@end


@implementation GSSocialDisconnectRequest

-(id) init{
	self = [super initWithType:@".SocialDisconnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSSocialDisconnectResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSSocialDisconnectResponse* gler = [[GSSocialDisconnectResponse alloc] initWithData:response];
        callback(gler);
    };
}


-(void) setSystemId:(NSString*) systemId{
	[self._data setObject:systemId forKey:@"systemId"];
}
@end


@implementation GSSocialLeaderboardDataRequest

-(id) init{
	self = [super initWithType:@".SocialLeaderboardDataRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSLeaderboardDataResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSLeaderboardDataResponse* gler = [[GSLeaderboardDataResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setDontErrorOnNotSocial:(BOOL) dontErrorOnNotSocial{
	[self._data setObject:[NSNumber numberWithBool:dontErrorOnNotSocial] forKey:@"dontErrorOnNotSocial"];
}
-(void) setEntryCount:(NSNumber*) entryCount{
	[self._data setObject:entryCount forKey:@"entryCount"];
}
-(void) setFriendIds:(NSArray*) friendIds{
	[self._data setObject:friendIds forKey:@"friendIds"];
}
-(void) setIncludeFirst:(NSNumber*) includeFirst{
	[self._data setObject:includeFirst forKey:@"includeFirst"];
}
-(void) setIncludeLast:(NSNumber*) includeLast{
	[self._data setObject:includeLast forKey:@"includeLast"];
}
-(void) setInverseSocial:(BOOL) inverseSocial{
	[self._data setObject:[NSNumber numberWithBool:inverseSocial] forKey:@"inverseSocial"];
}
-(void) setLeaderboardShortCode:(NSString*) leaderboardShortCode{
	[self._data setObject:leaderboardShortCode forKey:@"leaderboardShortCode"];
}
-(void) setOffset:(NSNumber*) offset{
	[self._data setObject:offset forKey:@"offset"];
}

-(void) setSocial:(BOOL) social{
	[self._data setObject:[NSNumber numberWithBool:social] forKey:@"social"];
}
-(void) setTeamIds:(NSArray*) teamIds{
	[self._data setObject:teamIds forKey:@"teamIds"];
}
-(void) setTeamTypes:(NSArray*) teamTypes{
	[self._data setObject:teamTypes forKey:@"teamTypes"];
}
@end


@implementation GSSocialStatusRequest

-(id) init{
	self = [super initWithType:@".SocialStatusRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSSocialStatusResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSSocialStatusResponse* gler = [[GSSocialStatusResponse alloc] initWithData:response];
        callback(gler);
    };
}


@end


@implementation GSSteamBuyGoodsRequest

-(id) init{
	self = [super initWithType:@".SteamBuyGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBuyVirtualGoodResponse* gler = [[GSBuyVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setCurrencyCode:(NSString*) currencyCode{
	[self._data setObject:currencyCode forKey:@"currencyCode"];
}
-(void) setOrderId:(NSString*) orderId{
	[self._data setObject:orderId forKey:@"orderId"];
}

-(void) setSubUnitPrice:(NSNumber*) subUnitPrice{
	[self._data setObject:subUnitPrice forKey:@"subUnitPrice"];
}
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer{
	[self._data setObject:[NSNumber numberWithBool:uniqueTransactionByPlayer] forKey:@"uniqueTransactionByPlayer"];
}
@end


@implementation GSSteamConnectRequest

-(id) init{
	self = [super initWithType:@".SteamConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSessionTicket:(NSString*) sessionTicket{
	[self._data setObject:sessionTicket forKey:@"sessionTicket"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSTwitchConnectRequest

-(id) init{
	self = [super initWithType:@".TwitchConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSTwitterConnectRequest

-(id) init{
	self = [super initWithType:@".TwitterConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessSecret:(NSString*) accessSecret{
	[self._data setObject:accessSecret forKey:@"accessSecret"];
}
-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSUpdateMessageRequest

-(id) init{
	self = [super initWithType:@".UpdateMessageRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSUpdateMessageResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSUpdateMessageResponse* gler = [[GSUpdateMessageResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setMessageId:(NSString*) messageId{
	[self._data setObject:messageId forKey:@"messageId"];
}

-(void) setStatus:(NSString*) status{
	[self._data setObject:status forKey:@"status"];
}
@end


@implementation GSViberConnectRequest

-(id) init{
	self = [super initWithType:@".ViberConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setDoNotRegisterForPush:(BOOL) doNotRegisterForPush{
	[self._data setObject:[NSNumber numberWithBool:doNotRegisterForPush] forKey:@"doNotRegisterForPush"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSWeChatConnectRequest

-(id) init{
	self = [super initWithType:@".WeChatConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setAccessToken:(NSString*) accessToken{
	[self._data setObject:accessToken forKey:@"accessToken"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}
-(void) setOpenId:(NSString*) openId{
	[self._data setObject:openId forKey:@"openId"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSWindowsBuyGoodsRequest

-(id) init{
	self = [super initWithType:@".WindowsBuyGoodsRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSBuyVirtualGoodResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSBuyVirtualGoodResponse* gler = [[GSBuyVirtualGoodResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setCurrencyCode:(NSString*) currencyCode{
	[self._data setObject:currencyCode forKey:@"currencyCode"];
}
-(void) setPlatform:(NSString*) platform{
	[self._data setObject:platform forKey:@"platform"];
}
-(void) setReceipt:(NSString*) receipt{
	[self._data setObject:receipt forKey:@"receipt"];
}

-(void) setSubUnitPrice:(NSNumber*) subUnitPrice{
	[self._data setObject:subUnitPrice forKey:@"subUnitPrice"];
}
-(void) setUniqueTransactionByPlayer:(BOOL) uniqueTransactionByPlayer{
	[self._data setObject:[NSNumber numberWithBool:uniqueTransactionByPlayer] forKey:@"uniqueTransactionByPlayer"];
}
@end


@implementation GSWithdrawChallengeRequest

-(id) init{
	self = [super initWithType:@".WithdrawChallengeRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSWithdrawChallengeResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSWithdrawChallengeResponse* gler = [[GSWithdrawChallengeResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setChallengeInstanceId:(NSString*) challengeInstanceId{
	[self._data setObject:challengeInstanceId forKey:@"challengeInstanceId"];
}
-(void) setMessage:(NSString*) message{
	[self._data setObject:message forKey:@"message"];
}

@end


@implementation GSXBOXLiveConnectRequest

-(id) init{
	self = [super initWithType:@".XBOXLiveConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDisplayName:(NSString*) displayName{
	[self._data setObject:displayName forKey:@"displayName"];
}
-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setStsTokenString:(NSString*) stsTokenString{
	[self._data setObject:stsTokenString forKey:@"stsTokenString"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
@end


@implementation GSXboxOneConnectRequest

-(id) init{
	self = [super initWithType:@".XboxOneConnectRequest"];
	return self;
}

-(BOOL) hasCallback{
	return self._callback != nil;
}

-(id) initWithData:(NSDictionary*) data{
	self = [super initWithData:data];
	return self;
}

-(void) setCallback:(void (^)(GSAuthenticationResponse*)) callback{
	self._callback = ^ (NSDictionary* response) {
        GSAuthenticationResponse* gler = [[GSAuthenticationResponse alloc] initWithData:response];
        callback(gler);
    };
}

-(void) setDoNotLinkToCurrentPlayer:(BOOL) doNotLinkToCurrentPlayer{
	[self._data setObject:[NSNumber numberWithBool:doNotLinkToCurrentPlayer] forKey:@"doNotLinkToCurrentPlayer"];
}
-(void) setErrorOnSwitch:(BOOL) errorOnSwitch{
	[self._data setObject:[NSNumber numberWithBool:errorOnSwitch] forKey:@"errorOnSwitch"];
}

-(void) setSandbox:(NSString*) sandbox{
	[self._data setObject:sandbox forKey:@"sandbox"];
}
-(void) setSegments:(NSDictionary*) segments{
	[self._data setObject:segments forKey:@"segments"];
}
-(void) setSwitchIfPossible:(BOOL) switchIfPossible{
	[self._data setObject:[NSNumber numberWithBool:switchIfPossible] forKey:@"switchIfPossible"];
}
-(void) setSyncDisplayName:(BOOL) syncDisplayName{
	[self._data setObject:[NSNumber numberWithBool:syncDisplayName] forKey:@"syncDisplayName"];
}
-(void) setToken:(NSString*) token{
	[self._data setObject:token forKey:@"token"];
}
@end


@interface GSMessageListener ()
	@property(copy)void(^_messageListener)(GSMessage*);
	@property(copy)void(^_achievementEarnedMessageListener)(GSAchievementEarnedMessage*);
	@property(copy)void(^_challengeAcceptedMessageListener)(GSChallengeAcceptedMessage*);
	@property(copy)void(^_challengeChangedMessageListener)(GSChallengeChangedMessage*);
	@property(copy)void(^_challengeChatMessageListener)(GSChallengeChatMessage*);
	@property(copy)void(^_challengeDeclinedMessageListener)(GSChallengeDeclinedMessage*);
	@property(copy)void(^_challengeDrawnMessageListener)(GSChallengeDrawnMessage*);
	@property(copy)void(^_challengeExpiredMessageListener)(GSChallengeExpiredMessage*);
	@property(copy)void(^_challengeIssuedMessageListener)(GSChallengeIssuedMessage*);
	@property(copy)void(^_challengeJoinedMessageListener)(GSChallengeJoinedMessage*);
	@property(copy)void(^_challengeLapsedMessageListener)(GSChallengeLapsedMessage*);
	@property(copy)void(^_challengeLostMessageListener)(GSChallengeLostMessage*);
	@property(copy)void(^_challengeStartedMessageListener)(GSChallengeStartedMessage*);
	@property(copy)void(^_challengeTurnTakenMessageListener)(GSChallengeTurnTakenMessage*);
	@property(copy)void(^_challengeWaitingMessageListener)(GSChallengeWaitingMessage*);
	@property(copy)void(^_challengeWithdrawnMessageListener)(GSChallengeWithdrawnMessage*);
	@property(copy)void(^_challengeWonMessageListener)(GSChallengeWonMessage*);
	@property(copy)void(^_friendMessageListener)(GSFriendMessage*);
	@property(copy)void(^_globalRankChangedMessageListener)(GSGlobalRankChangedMessage*);
	@property(copy)void(^_matchFoundMessageListener)(GSMatchFoundMessage*);
	@property(copy)void(^_matchNotFoundMessageListener)(GSMatchNotFoundMessage*);
	@property(copy)void(^_matchUpdatedMessageListener)(GSMatchUpdatedMessage*);
	@property(copy)void(^_newHighScoreMessageListener)(GSNewHighScoreMessage*);
	@property(copy)void(^_newTeamScoreMessageListener)(GSNewTeamScoreMessage*);
	@property(copy)void(^_scriptMessageListener)(GSScriptMessage*);
	@property(copy)void(^_sessionTerminatedMessageListener)(GSSessionTerminatedMessage*);
	@property(copy)void(^_socialRankChangedMessageListener)(GSSocialRankChangedMessage*);
	@property(copy)void(^_teamChatMessageListener)(GSTeamChatMessage*);
	@property(copy)void(^_teamRankChangedMessageListener)(GSTeamRankChangedMessage*);
	@property(copy)void(^_uploadCompleteMessageListener)(GSUploadCompleteMessage*);
@end

@implementation GSMessageListener
	-(void) onMessage:(void (^)(GSMessage*))messageListener{
		self._messageListener = messageListener;
	}
	-(void) onGSAchievementEarnedMessage:(void (^)(GSAchievementEarnedMessage*))achievementEarnedMessageListener{
		self._achievementEarnedMessageListener = achievementEarnedMessageListener;
	}
	-(void) onGSChallengeAcceptedMessage:(void (^)(GSChallengeAcceptedMessage*))challengeAcceptedMessageListener{
		self._challengeAcceptedMessageListener = challengeAcceptedMessageListener;
	}
	-(void) onGSChallengeChangedMessage:(void (^)(GSChallengeChangedMessage*))challengeChangedMessageListener{
		self._challengeChangedMessageListener = challengeChangedMessageListener;
	}
	-(void) onGSChallengeChatMessage:(void (^)(GSChallengeChatMessage*))challengeChatMessageListener{
		self._challengeChatMessageListener = challengeChatMessageListener;
	}
	-(void) onGSChallengeDeclinedMessage:(void (^)(GSChallengeDeclinedMessage*))challengeDeclinedMessageListener{
		self._challengeDeclinedMessageListener = challengeDeclinedMessageListener;
	}
	-(void) onGSChallengeDrawnMessage:(void (^)(GSChallengeDrawnMessage*))challengeDrawnMessageListener{
		self._challengeDrawnMessageListener = challengeDrawnMessageListener;
	}
	-(void) onGSChallengeExpiredMessage:(void (^)(GSChallengeExpiredMessage*))challengeExpiredMessageListener{
		self._challengeExpiredMessageListener = challengeExpiredMessageListener;
	}
	-(void) onGSChallengeIssuedMessage:(void (^)(GSChallengeIssuedMessage*))challengeIssuedMessageListener{
		self._challengeIssuedMessageListener = challengeIssuedMessageListener;
	}
	-(void) onGSChallengeJoinedMessage:(void (^)(GSChallengeJoinedMessage*))challengeJoinedMessageListener{
		self._challengeJoinedMessageListener = challengeJoinedMessageListener;
	}
	-(void) onGSChallengeLapsedMessage:(void (^)(GSChallengeLapsedMessage*))challengeLapsedMessageListener{
		self._challengeLapsedMessageListener = challengeLapsedMessageListener;
	}
	-(void) onGSChallengeLostMessage:(void (^)(GSChallengeLostMessage*))challengeLostMessageListener{
		self._challengeLostMessageListener = challengeLostMessageListener;
	}
	-(void) onGSChallengeStartedMessage:(void (^)(GSChallengeStartedMessage*))challengeStartedMessageListener{
		self._challengeStartedMessageListener = challengeStartedMessageListener;
	}
	-(void) onGSChallengeTurnTakenMessage:(void (^)(GSChallengeTurnTakenMessage*))challengeTurnTakenMessageListener{
		self._challengeTurnTakenMessageListener = challengeTurnTakenMessageListener;
	}
	-(void) onGSChallengeWaitingMessage:(void (^)(GSChallengeWaitingMessage*))challengeWaitingMessageListener{
		self._challengeWaitingMessageListener = challengeWaitingMessageListener;
	}
	-(void) onGSChallengeWithdrawnMessage:(void (^)(GSChallengeWithdrawnMessage*))challengeWithdrawnMessageListener{
		self._challengeWithdrawnMessageListener = challengeWithdrawnMessageListener;
	}
	-(void) onGSChallengeWonMessage:(void (^)(GSChallengeWonMessage*))challengeWonMessageListener{
		self._challengeWonMessageListener = challengeWonMessageListener;
	}
	-(void) onGSFriendMessage:(void (^)(GSFriendMessage*))friendMessageListener{
		self._friendMessageListener = friendMessageListener;
	}
	-(void) onGSGlobalRankChangedMessage:(void (^)(GSGlobalRankChangedMessage*))globalRankChangedMessageListener{
		self._globalRankChangedMessageListener = globalRankChangedMessageListener;
	}
	-(void) onGSMatchFoundMessage:(void (^)(GSMatchFoundMessage*))matchFoundMessageListener{
		self._matchFoundMessageListener = matchFoundMessageListener;
	}
	-(void) onGSMatchNotFoundMessage:(void (^)(GSMatchNotFoundMessage*))matchNotFoundMessageListener{
		self._matchNotFoundMessageListener = matchNotFoundMessageListener;
	}
	-(void) onGSMatchUpdatedMessage:(void (^)(GSMatchUpdatedMessage*))matchUpdatedMessageListener{
		self._matchUpdatedMessageListener = matchUpdatedMessageListener;
	}
	-(void) onGSNewHighScoreMessage:(void (^)(GSNewHighScoreMessage*))newHighScoreMessageListener{
		self._newHighScoreMessageListener = newHighScoreMessageListener;
	}
	-(void) onGSNewTeamScoreMessage:(void (^)(GSNewTeamScoreMessage*))newTeamScoreMessageListener{
		self._newTeamScoreMessageListener = newTeamScoreMessageListener;
	}
	-(void) onGSScriptMessage:(void (^)(GSScriptMessage*))scriptMessageListener{
		self._scriptMessageListener = scriptMessageListener;
	}
	-(void) onGSSessionTerminatedMessage:(void (^)(GSSessionTerminatedMessage*))sessionTerminatedMessageListener{
		self._sessionTerminatedMessageListener = sessionTerminatedMessageListener;
	}
	-(void) onGSSocialRankChangedMessage:(void (^)(GSSocialRankChangedMessage*))socialRankChangedMessageListener{
		self._socialRankChangedMessageListener = socialRankChangedMessageListener;
	}
	-(void) onGSTeamChatMessage:(void (^)(GSTeamChatMessage*))teamChatMessageListener{
		self._teamChatMessageListener = teamChatMessageListener;
	}
	-(void) onGSTeamRankChangedMessage:(void (^)(GSTeamRankChangedMessage*))teamRankChangedMessageListener{
		self._teamRankChangedMessageListener = teamRankChangedMessageListener;
	}
	-(void) onGSUploadCompleteMessage:(void (^)(GSUploadCompleteMessage*))uploadCompleteMessageListener{
		self._uploadCompleteMessageListener = uploadCompleteMessageListener;
	}

	-(void) processMessage:(NSDictionary*) message withType:(NSString*) type{
		if(false){}
		else if([type isEqualToString:@".AchievementEarnedMessage"]){
			if(self._achievementEarnedMessageListener || self._messageListener) {
				
				GSAchievementEarnedMessage* messageClass = [[GSAchievementEarnedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._achievementEarnedMessageListener) {
					self._achievementEarnedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeAcceptedMessage"]){
			if(self._challengeAcceptedMessageListener || self._messageListener) {
				
				GSChallengeAcceptedMessage* messageClass = [[GSChallengeAcceptedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeAcceptedMessageListener) {
					self._challengeAcceptedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeChangedMessage"]){
			if(self._challengeChangedMessageListener || self._messageListener) {
				
				GSChallengeChangedMessage* messageClass = [[GSChallengeChangedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeChangedMessageListener) {
					self._challengeChangedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeChatMessage"]){
			if(self._challengeChatMessageListener || self._messageListener) {
				
				GSChallengeChatMessage* messageClass = [[GSChallengeChatMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeChatMessageListener) {
					self._challengeChatMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeDeclinedMessage"]){
			if(self._challengeDeclinedMessageListener || self._messageListener) {
				
				GSChallengeDeclinedMessage* messageClass = [[GSChallengeDeclinedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeDeclinedMessageListener) {
					self._challengeDeclinedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeDrawnMessage"]){
			if(self._challengeDrawnMessageListener || self._messageListener) {
				
				GSChallengeDrawnMessage* messageClass = [[GSChallengeDrawnMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeDrawnMessageListener) {
					self._challengeDrawnMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeExpiredMessage"]){
			if(self._challengeExpiredMessageListener || self._messageListener) {
				
				GSChallengeExpiredMessage* messageClass = [[GSChallengeExpiredMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeExpiredMessageListener) {
					self._challengeExpiredMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeIssuedMessage"]){
			if(self._challengeIssuedMessageListener || self._messageListener) {
				
				GSChallengeIssuedMessage* messageClass = [[GSChallengeIssuedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeIssuedMessageListener) {
					self._challengeIssuedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeJoinedMessage"]){
			if(self._challengeJoinedMessageListener || self._messageListener) {
				
				GSChallengeJoinedMessage* messageClass = [[GSChallengeJoinedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeJoinedMessageListener) {
					self._challengeJoinedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeLapsedMessage"]){
			if(self._challengeLapsedMessageListener || self._messageListener) {
				
				GSChallengeLapsedMessage* messageClass = [[GSChallengeLapsedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeLapsedMessageListener) {
					self._challengeLapsedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeLostMessage"]){
			if(self._challengeLostMessageListener || self._messageListener) {
				
				GSChallengeLostMessage* messageClass = [[GSChallengeLostMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeLostMessageListener) {
					self._challengeLostMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeStartedMessage"]){
			if(self._challengeStartedMessageListener || self._messageListener) {
				
				GSChallengeStartedMessage* messageClass = [[GSChallengeStartedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeStartedMessageListener) {
					self._challengeStartedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeTurnTakenMessage"]){
			if(self._challengeTurnTakenMessageListener || self._messageListener) {
				
				GSChallengeTurnTakenMessage* messageClass = [[GSChallengeTurnTakenMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeTurnTakenMessageListener) {
					self._challengeTurnTakenMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeWaitingMessage"]){
			if(self._challengeWaitingMessageListener || self._messageListener) {
				
				GSChallengeWaitingMessage* messageClass = [[GSChallengeWaitingMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeWaitingMessageListener) {
					self._challengeWaitingMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeWithdrawnMessage"]){
			if(self._challengeWithdrawnMessageListener || self._messageListener) {
				
				GSChallengeWithdrawnMessage* messageClass = [[GSChallengeWithdrawnMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeWithdrawnMessageListener) {
					self._challengeWithdrawnMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ChallengeWonMessage"]){
			if(self._challengeWonMessageListener || self._messageListener) {
				
				GSChallengeWonMessage* messageClass = [[GSChallengeWonMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._challengeWonMessageListener) {
					self._challengeWonMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".FriendMessage"]){
			if(self._friendMessageListener || self._messageListener) {
				
				GSFriendMessage* messageClass = [[GSFriendMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._friendMessageListener) {
					self._friendMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".GlobalRankChangedMessage"]){
			if(self._globalRankChangedMessageListener || self._messageListener) {
				
				GSGlobalRankChangedMessage* messageClass = [[GSGlobalRankChangedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._globalRankChangedMessageListener) {
					self._globalRankChangedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".MatchFoundMessage"]){
			if(self._matchFoundMessageListener || self._messageListener) {
				
				GSMatchFoundMessage* messageClass = [[GSMatchFoundMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._matchFoundMessageListener) {
					self._matchFoundMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".MatchNotFoundMessage"]){
			if(self._matchNotFoundMessageListener || self._messageListener) {
				
				GSMatchNotFoundMessage* messageClass = [[GSMatchNotFoundMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._matchNotFoundMessageListener) {
					self._matchNotFoundMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".MatchUpdatedMessage"]){
			if(self._matchUpdatedMessageListener || self._messageListener) {
				
				GSMatchUpdatedMessage* messageClass = [[GSMatchUpdatedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._matchUpdatedMessageListener) {
					self._matchUpdatedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".NewHighScoreMessage"]){
			if(self._newHighScoreMessageListener || self._messageListener) {
				
				GSNewHighScoreMessage* messageClass = [[GSNewHighScoreMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._newHighScoreMessageListener) {
					self._newHighScoreMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".NewTeamScoreMessage"]){
			if(self._newTeamScoreMessageListener || self._messageListener) {
				
				GSNewTeamScoreMessage* messageClass = [[GSNewTeamScoreMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._newTeamScoreMessageListener) {
					self._newTeamScoreMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".ScriptMessage"]){
			if(self._scriptMessageListener || self._messageListener) {
				
				GSScriptMessage* messageClass = [[GSScriptMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._scriptMessageListener) {
					self._scriptMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".SessionTerminatedMessage"]){
			if(self._sessionTerminatedMessageListener || self._messageListener) {
				
				GSSessionTerminatedMessage* messageClass = [[GSSessionTerminatedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._sessionTerminatedMessageListener) {
					self._sessionTerminatedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".SocialRankChangedMessage"]){
			if(self._socialRankChangedMessageListener || self._messageListener) {
				
				GSSocialRankChangedMessage* messageClass = [[GSSocialRankChangedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._socialRankChangedMessageListener) {
					self._socialRankChangedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".TeamChatMessage"]){
			if(self._teamChatMessageListener || self._messageListener) {
				
				GSTeamChatMessage* messageClass = [[GSTeamChatMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._teamChatMessageListener) {
					self._teamChatMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".TeamRankChangedMessage"]){
			if(self._teamRankChangedMessageListener || self._messageListener) {
				
				GSTeamRankChangedMessage* messageClass = [[GSTeamRankChangedMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._teamRankChangedMessageListener) {
					self._teamRankChangedMessageListener(messageClass);
				}
			}
		}
		else if([type isEqualToString:@".UploadCompleteMessage"]){
			if(self._uploadCompleteMessageListener || self._messageListener) {
				
				GSUploadCompleteMessage* messageClass = [[GSUploadCompleteMessage alloc] initWithData:message];
				
				if(self._messageListener) {
					self._messageListener(messageClass);
				}
				if(self._uploadCompleteMessageListener) {
					self._uploadCompleteMessageListener(messageClass);
				}
			}
		}
	}

@end

@implementation GSRequestBuilder : NSObject
	+(GSRequest*) buildRequest:(NSDictionary*)data{
		GSRequest* request;
		NSString* type = [data objectForKey:@"@class"];
		if(false){}
		else if([type isEqualToString:@".AcceptChallengeRequest"]){
			request = [[GSAcceptChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".AccountDetailsRequest"]){
			request = [[GSAccountDetailsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".AmazonBuyGoodsRequest"]){
			request = [[GSAmazonBuyGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".AmazonConnectRequest"]){
			request = [[GSAmazonConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".AnalyticsRequest"]){
			request = [[GSAnalyticsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".AroundMeLeaderboardRequest"]){
			request = [[GSAroundMeLeaderboardRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".AuthenticationRequest"]){
			request = [[GSAuthenticationRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".BatchAdminRequest"]){
			request = [[GSBatchAdminRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".BuyVirtualGoodsRequest"]){
			request = [[GSBuyVirtualGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".CancelBulkJobAdminRequest"]){
			request = [[GSCancelBulkJobAdminRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ChangeUserDetailsRequest"]){
			request = [[GSChangeUserDetailsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ChatOnChallengeRequest"]){
			request = [[GSChatOnChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ConsumeVirtualGoodRequest"]){
			request = [[GSConsumeVirtualGoodRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".CreateChallengeRequest"]){
			request = [[GSCreateChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".CreateTeamRequest"]){
			request = [[GSCreateTeamRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".DeclineChallengeRequest"]){
			request = [[GSDeclineChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".DeviceAuthenticationRequest"]){
			request = [[GSDeviceAuthenticationRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".DismissMessageRequest"]){
			request = [[GSDismissMessageRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".DismissMultipleMessagesRequest"]){
			request = [[GSDismissMultipleMessagesRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".DropTeamRequest"]){
			request = [[GSDropTeamRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".EndSessionRequest"]){
			request = [[GSEndSessionRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".FacebookConnectRequest"]){
			request = [[GSFacebookConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".FindChallengeRequest"]){
			request = [[GSFindChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".FindMatchRequest"]){
			request = [[GSFindMatchRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".FindPendingMatchesRequest"]){
			request = [[GSFindPendingMatchesRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GameCenterConnectRequest"]){
			request = [[GSGameCenterConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetChallengeRequest"]){
			request = [[GSGetChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetDownloadableRequest"]){
			request = [[GSGetDownloadableRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetLeaderboardEntriesRequest"]){
			request = [[GSGetLeaderboardEntriesRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetMessageRequest"]){
			request = [[GSGetMessageRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetMyTeamsRequest"]){
			request = [[GSGetMyTeamsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetPropertyRequest"]){
			request = [[GSGetPropertyRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetPropertySetRequest"]){
			request = [[GSGetPropertySetRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetTeamRequest"]){
			request = [[GSGetTeamRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetUploadUrlRequest"]){
			request = [[GSGetUploadUrlRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GetUploadedRequest"]){
			request = [[GSGetUploadedRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GooglePlayBuyGoodsRequest"]){
			request = [[GSGooglePlayBuyGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GooglePlayConnectRequest"]){
			request = [[GSGooglePlayConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".GooglePlusConnectRequest"]){
			request = [[GSGooglePlusConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".IOSBuyGoodsRequest"]){
			request = [[GSIOSBuyGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".JoinChallengeRequest"]){
			request = [[GSJoinChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".JoinPendingMatchRequest"]){
			request = [[GSJoinPendingMatchRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".JoinTeamRequest"]){
			request = [[GSJoinTeamRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".KongregateConnectRequest"]){
			request = [[GSKongregateConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".LeaderboardDataRequest"]){
			request = [[GSLeaderboardDataRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".LeaderboardsEntriesRequest"]){
			request = [[GSLeaderboardsEntriesRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".LeaveTeamRequest"]){
			request = [[GSLeaveTeamRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListAchievementsRequest"]){
			request = [[GSListAchievementsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListBulkJobsAdminRequest"]){
			request = [[GSListBulkJobsAdminRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListChallengeRequest"]){
			request = [[GSListChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListChallengeTypeRequest"]){
			request = [[GSListChallengeTypeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListGameFriendsRequest"]){
			request = [[GSListGameFriendsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListInviteFriendsRequest"]){
			request = [[GSListInviteFriendsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListLeaderboardsRequest"]){
			request = [[GSListLeaderboardsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListMessageDetailRequest"]){
			request = [[GSListMessageDetailRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListMessageRequest"]){
			request = [[GSListMessageRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListMessageSummaryRequest"]){
			request = [[GSListMessageSummaryRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListTeamChatRequest"]){
			request = [[GSListTeamChatRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListTeamsRequest"]){
			request = [[GSListTeamsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListTransactionsRequest"]){
			request = [[GSListTransactionsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ListVirtualGoodsRequest"]){
			request = [[GSListVirtualGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".LogChallengeEventRequest"]){
			request = [[GSLogChallengeEventRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".LogEventRequest"]){
			request = [[GSLogEventRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".MatchDetailsRequest"]){
			request = [[GSMatchDetailsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".MatchmakingRequest"]){
			request = [[GSMatchmakingRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".NXConnectRequest"]){
			request = [[GSNXConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".PSNConnectRequest"]){
			request = [[GSPSNConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".PsnBuyGoodsRequest"]){
			request = [[GSPsnBuyGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".PushRegistrationRequest"]){
			request = [[GSPushRegistrationRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".QQConnectRequest"]){
			request = [[GSQQConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".RegistrationRequest"]){
			request = [[GSRegistrationRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".RevokePurchaseGoodsRequest"]){
			request = [[GSRevokePurchaseGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ScheduleBulkJobAdminRequest"]){
			request = [[GSScheduleBulkJobAdminRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".SendFriendMessageRequest"]){
			request = [[GSSendFriendMessageRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".SendTeamChatMessageRequest"]){
			request = [[GSSendTeamChatMessageRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".SocialDisconnectRequest"]){
			request = [[GSSocialDisconnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".SocialLeaderboardDataRequest"]){
			request = [[GSSocialLeaderboardDataRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".SocialStatusRequest"]){
			request = [[GSSocialStatusRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".SteamBuyGoodsRequest"]){
			request = [[GSSteamBuyGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".SteamConnectRequest"]){
			request = [[GSSteamConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".TwitchConnectRequest"]){
			request = [[GSTwitchConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".TwitterConnectRequest"]){
			request = [[GSTwitterConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".UpdateMessageRequest"]){
			request = [[GSUpdateMessageRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".ViberConnectRequest"]){
			request = [[GSViberConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".WeChatConnectRequest"]){
			request = [[GSWeChatConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".WindowsBuyGoodsRequest"]){
			request = [[GSWindowsBuyGoodsRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".WithdrawChallengeRequest"]){
			request = [[GSWithdrawChallengeRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".XBOXLiveConnectRequest"]){
			request = [[GSXBOXLiveConnectRequest alloc] initWithData:data];
		}
		else if([type isEqualToString:@".XboxOneConnectRequest"]){
			request = [[GSXboxOneConnectRequest alloc] initWithData:data];
		}
		[request setTimeout:5];
		return request;
	}
@end


