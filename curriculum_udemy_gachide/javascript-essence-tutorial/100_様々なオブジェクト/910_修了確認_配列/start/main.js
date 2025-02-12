/**
 * 問題：
 * Arrayを継承して以下のメソッドを実装してみましょう。
 * 
 * push(*1)
 * forEach
 * map
 * filter
 * reduce
 * 
 * *1:pushはチェーンメソッドとしてつなげられるように実装してみてください。
 */
class MyArray extends Array {
	constructor(...args) {
		super(...args)
	}

	print(label = '') {
		console.log(`%c ${label}`, 'color: blue; font-weight: 600;', this);
		return this;
	}

	push(...values) {
		this.splice(this.length, values.length, ...values);
		return this;
	}

	forEach(cb) {
		for(const key in this) {
			cb.call(null, this[key], key, this);
		}
		return this;
	}

	map(cb) {
		for(const key in this) {
			const res = cb.call(null, this[key], key, this);
			this.splice(key, 1, res);
		}
		return this;
	}

	filter(cb) {
		for(const key in this) {
			if (!(cb.call(null, this[key], key, this))) {
				this.splice(key, 1);
			}
		}
		return this;
	}

	reduce(cb, defo) {
		let tmpThis = [...this];
		let acc = defo;
		if(defo === undefined) { acc = tmpThis.splice(0, 1)[0] }
		for(const key in tmpThis) {
			acc = cb.call(null, acc, tmpThis[key]);
		}
		return acc;
	}
}

function double(v, i, obj) {
	return v * 2;
}

const original = new MyArray(1, 2, 3, 4);

const result = original
	.map(double)
	.push(5)
	.filter(function (v, i) {
		return v > 2;
	})
	.reduce(function(accu, curr) {
		return accu + curr;
	})

console.log('%coriginal', 'color: blue; font-weight: bold;', original);
console.log('%cresult', 'color: red; font-weight: bold;', result);

