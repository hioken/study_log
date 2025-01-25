// let a = 2;
// window.a = 4;
// function fn1() {
//     // let a = 1;
//     function fn2() {
//         console.log(a);
        
//         if(true) {
//             var a = 3;
//         }
        
//     }
//     fn2();
// }
// fn1();



let a = 2;
function fn1() {
    let b = 1;
    function fn2() {
        let c = 3;
        // let b = 200;
        console.log(b);
        // let b = 2;
        const b = 2;
    }
    fn2();
}
fn1();



