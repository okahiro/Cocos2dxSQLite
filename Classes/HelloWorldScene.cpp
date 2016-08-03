#include "HelloWorldScene.h"

#include "DataManager.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
	
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	Size winSize = Director::getInstance()->getWinSize();
	
	// idラベル
	Label *idLabel = Label::createWithSystemFont("id", "", 24);
	idLabel->setPosition(Vec2(winSize.width * 0.1f,winSize.height * 0.95f));
	this->addChild(idLabel);
	// id入力ボックス
	ui::EditBox *idEditBox = ui::EditBox::create(Size(100, 50), ui::Scale9Sprite::create("res/EditBoxBG.png"));
	idEditBox->setPosition(Vec2(winSize.width * 0.2f, winSize.height * 0.95f));
	idEditBox->setAnchorPoint(Vec2(0,0.5f));
	idEditBox->setFontSize(24);
	idEditBox->setFontColor(Color3B::WHITE);
	idEditBox->setMaxLength(12);
	idEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	idEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(idEditBox);
	
	// nameラベル
	Label *nameLabel = Label::createWithSystemFont("name", "", 24);
	nameLabel->setPosition(Vec2(winSize.width * 0.1f,winSize.height * 0.89f));
	this->addChild(nameLabel);
	// name入力ボックス
	ui::EditBox *nameEditBox = ui::EditBox::create(Size(300, 50), ui::Scale9Sprite::create("res/EditBoxBG.png"));
	nameEditBox->setPosition(Vec2(winSize.width * 0.2f, winSize.height * 0.89f));
	nameEditBox->setAnchorPoint(Vec2(0,0.5f));
	nameEditBox->setFontSize(24);
	nameEditBox->setFontColor(Color3B::WHITE);
	nameEditBox->setMaxLength(12);
	nameEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	nameEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(nameEditBox);
	
	// weightラベル
	Label *weightLabel = Label::createWithSystemFont("weight", "", 24);
	weightLabel->setPosition(Vec2(winSize.width * 0.1f,winSize.height * 0.83f));
	this->addChild(weightLabel);
	// weight入力ボックス
	ui::EditBox *weightEditBox = ui::EditBox::create(Size(100, 50), ui::Scale9Sprite::create("res/EditBoxBG.png"));
	weightEditBox->setPosition(Vec2(winSize.width * 0.2f, winSize.height * 0.83f));
	weightEditBox->setAnchorPoint(Vec2(0,0.5f));
	weightEditBox->setFontSize(24);
	weightEditBox->setFontColor(Color3B::WHITE);
	weightEditBox->setMaxLength(12);
	weightEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	weightEditBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(weightEditBox);
	
	// 登録／更新ボタン
	ui::Button *insertOrUpdateButton = ui::Button::create();
	insertOrUpdateButton->setTitleText("登録/更新");
	insertOrUpdateButton->setTitleFontSize(24);
	insertOrUpdateButton->setPosition(Vec2(winSize.width * 0.8f,winSize.height * 0.9f));
	insertOrUpdateButton->addTouchEventListener([=](Ref* pSender,ui::Widget::TouchEventType type)
	 {
		 if(type == ui::Widget::TouchEventType::ENDED)
		 {
			 int id = Value(idEditBox->getText()).asInt();
			 std::string name = nameEditBox->getText();
			 float weight = Value(weightEditBox->getText()).asFloat();
			 
			 DataManager::getInstance()->insertOrUpdateUnitData(id, name, weight);
			 
			 this->refreshList();
		 }
	 });
	this->addChild(insertOrUpdateButton);
	
	// リストボックス
	ui::ListView *listView = ui::ListView::create();
	listView->setContentSize(Size(600,winSize.height * 0.5f));
	listView->setPosition(Vec2(20,20));
	listView->setBackGroundColor(Color3B::WHITE);
	listView->setTag(99);
	this->addChild(listView);
	
	
	// テーブル作成（テーブルがすでにある場合は作成されない）
	DataManager::getInstance()->createTable();
	
	this->refreshList();
	
    return true;
}

// データベースの内容を検索して画面に表示
void HelloWorld::refreshList()
{
	// ListViewを取得
	ui::ListView *listView = (ui::ListView*)this->getChildByTag(99);
	listView->removeAllItems();
	
	// データベースから検索
	Vector<UnitData*> unitDataList = DataManager::getInstance()->selectUnitDataList();
	
	for(auto unitData : unitDataList)
	{
		// ボタンを追加
		ui::Button *button = ui::Button::create();
		button->setTitleText(StringUtils::format("【%d】%s %f",unitData->_id,unitData->_name.c_str(),unitData->_weight));
		button->setTitleFontSize(26);
		listView->pushBackCustomItem(button);
	}
}
