/**
 * 問題：
 * 【修了確認】コールバック関数で実装したcalcFactoryを
 * １秒後にconsole.logまたはalertで計算式が表示される
 * ようにcalcFactory関数内の実装を変更してみてください。
 */
function calcFactory(val, callback) {
    function callback1s(arg) {
        setTimeout(() => {callback(arg)}, 1000);
    }
    return {
        plus: function(target) {
            const newVal = val + target;
            // const fn = function() {callback(`${val} + ${target} = ${newVal}`)};
            // setTimeout(fn, 1000)
            callback1s(`${val} + ${target} = ${newVal}`)

            val = newVal;
        },
        minus: function(target) {
            const newVal = val - target;
            callback(`${val} - ${target} = ${newVal}`);
            val = newVal;
        },
        multiply: function(target) {
            const newVal = val * target;
            callback(`${val} x ${target} = ${newVal}`);
            val = newVal;
        },
        divide: function(target) {
            const newVal = val / target;
            callback(`${val} / ${target} = ${newVal}`);
            val = newVal;
        }
    };
}

const calc = calcFactory(10, console.log);
calc.plus(5); 
calc.minus(3); 
calc.multiply(3);
calc.divide(2);