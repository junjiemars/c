use serde::{Deserialize, Serialize};
use std::f64;
use warp::Filter;

#[tokio::main]
async fn main() {
    let root = warp::path::end().map(|| "Welcome to RESTFull World!");

    let math_root = warp::path("math");
    let math_sqrt = warp::path!("sqrt" / f64).map(|x: f64| format!("sqrt({}) = {}", x, x.sqrt()));
    let math_expt = warp::path!("expt" / f64).map(|x: f64| format!("expt({} = {})", x, x.exp2()));
    let math_log = warp::path!("log" / f64).map(|x: f64| format!("log({}) = {}", x, x.log2()));
    let math_help = math_root
        .and(warp::path::end())
        .map(|| "The Math API: /math/sqrt/:f64, /math/expt/:f64");
    let math = math_help.or(math_root.and(math_sqrt.or(math_expt).or(math_log)));

    let class_root = warp::path("class");
    let class_verify = warp::post()
        .and(class_root)
        .and(warp::path("verify"))
        .and(warp::path::param::<u32>())
        .and(warp::body::content_length_limit(1024 * 16))
        .and(warp::body::json())
        .map(|no: u32, mut stu: Student| {
            stu.no = 100 + no;
            warp::reply::json(&stu)
        });
    let class_help = class_root
        .and(warp::get())
        .and(warp::path::end())
        .map(|| "The Class API: /class/verify/:u32");
    let class = class_help.or(class_verify);

    // GET /
    // GET /math
    // GET /math/sqrt/:f64
    // GET /math/expt/:f64
    // GET /math/log/:f64
    // GET /class/
    // POST /class/verify/:u32
    let routes = root.or(math).or(class);

    warp::serve(routes).run(([127, 0, 0, 1], 9090)).await;
}

#[derive(Deserialize, Serialize, Clone)]
struct Student {
    name: String,
    no: u32,
}
