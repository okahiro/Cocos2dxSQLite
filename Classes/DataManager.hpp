//
//  DataManager.hpp
//  Cocos2dxSQLiteSample
//
//  Created by おかひろ on 2016/08/02.
//
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include "cocos2d.h"
#include "sqlite3.h"

#define DB_FILE_NAME_ENC "EncryptedDB.db"	// データベースを暗号化する場合のファイル名
#define ENCRYPT_DB_PASSWORD "23da3i3kJLale"	// データベースを暗号化する場合のパスワード

USING_NS_CC;

class UnitData : public Node
{
public:
	int _id;
	std::string _name;
	float _weight;
	
	CREATE_FUNC(UnitData);
};


class DataManager
{
private:
	static DataManager* mManager;
	
	// データベースファイルを開いた時に記憶しておく時間（処理時間計測用）
	std::chrono::system_clock::time_point _dbOpenTime;
public:
	DataManager();
	
	static DataManager* getInstance();
	
	sqlite3* openDB();
	sqlite3* openDBAndStartTransaction();
	bool closeDB(sqlite3 *db);
	bool commitTransactionAndCloseDB(sqlite3 *db);
	
	void createTable();
	
	void insertOrUpdateUnitData(int id,std::string name,float weight);
	Vector<UnitData*> selectUnitDataList();
};

#endif /* DataManager_hpp */
