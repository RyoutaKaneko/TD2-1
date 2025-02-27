#pragma once
#include "math/Vector3.h"
#include <Model.h>
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include <affin.h>

//当たり判定用AABB
typedef struct AABB {
	Vector3 min_;
	Vector3 size_;
};

class PlayerBullet {
  public:
	///< summary>
	///初期化
	///</summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	///< summary>
	///初期化
	///</summary>
	void Update();

	///< summary>
	///初期化
	///</summary>
	void Draw(const ViewProjection& viewProjection);

	bool CheckHit(Vector3 boss);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();


  public:
	bool InDead() const { return isDead_; }
	int GetR() { return r; }

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;
	
	//寿命
	static const int32_t kLifeTime = 60 * 3;
	//デス大麻
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	int r = 2;
	
};
