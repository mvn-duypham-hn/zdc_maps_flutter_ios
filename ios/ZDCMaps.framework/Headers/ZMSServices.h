//
//  ZMSServices.h
//  ZDCMaps
//
//  Created by s_hirose on 2016/09/29.
//  Copyright © 2016年 ZENRIN DataCom. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// ## サービス利用者認証クラス
/// @note 初期化不可
@interface ZMSServices : NSObject

// MARK: - メソッド

/// ### 認証パラメータを指定してサービス利用を開始する
/// @warning 地図を生成する前に実行する。<br>2度呼んだ場合はNOが返る。
/// @param consumerKey: コンシューマーキー (クライアントID)
/// @param secretKey: 秘密鍵
/// @param certificateDomain: 認証ドメイン
/// @return 成功(YES) / 失敗(NO)
+ (BOOL)provideConsumerKey:(NSString *)consumerKey secretKey:(NSString *)secretKey certificateDomain:(NSString *)certificateDomain;

/// :nodoc:
- (instancetype)init __attribute__((unavailable("init is not available")));

@end

NS_ASSUME_NONNULL_END
