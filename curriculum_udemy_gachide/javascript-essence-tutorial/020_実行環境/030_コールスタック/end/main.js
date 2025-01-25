// デバッグ手順確認
// デベロッパーツール > Sources
// step操作やブレイクポイントの設定が可能
function a() {
}
function b() {
    a();
}
function c() {
    b();
}
c();
