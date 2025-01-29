/**
 * 問題：
 * 電卓の入力と同じような挙動をするチェーンメソッド
 * を作成してみましょう。
 * 
 * 例えば、次のように使用し、結果が表示
 * されるようにします。
 * 
 * 
 * 例１）
 * const calc = new Calculator();
 * 
 * calc.set(10)
 * .minus()
 * .set(3) -> '7'を出力(10 - 3)
 * 
 * 例２）
 * const calc = new Calculator();
 * 
 * calc.set(10)
 * 	.minus()
 * 	.set(3) -> '7'を出力
 * 	.mutiply()
 * 	.set(6) -> '42'を出力（10 - 3) * 6
 */


class Calculator {
	constructor() { 
		this.total = 0;
	}

	set(nextNum) {
		if (nextNum) { this.nextNum = nextNum }
		if (this.operation) {
			this.operation.call(this)
			console.log(this.total)
		} else {
			this.total = this.nextNum
		}
		return this;
	}

	plus() {
		this.operation = function() { this.total = this.total + this.nextNum } 
		return this;
	}

	minus() {
		this.operation = function() { this.total = this.total - this.nextNum } 
		return this;
	}

	mutiply() {
		this.operation = function() { this.total = this.total * this.nextNum } 
		return this;
	}

	divide() {
		this.operation = function() { this.total = this.total / this.nextNum } 
		return this;
	}
}

const calc = new Calculator();

calc.set(10)
	.minus()
	.set(3)
	.mutiply()
	.set(6)
	.divide()
	.set(2)
	.plus()
	.set(2)
