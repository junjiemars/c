use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::f64;
use warp::{
    http::{Response, StatusCode},
    Filter,
};

#[tokio::main]
async fn main() {
    let root = warp::path::end().map(|| "Welcome to RESTFull World!");

    let math_root = warp::path("math");
    let math_sqrt = warp::get()
        .and(math_root)
        .and(warp::path("sqrt"))
        .and(warp::path::param::<f64>())
        .map(|x: f64| format!("sqrt({}) = {}", x, x.sqrt()));
    let math_expt = warp::get()
        .and(math_root)
        .and(warp::path("expt"))
        .and(warp::path::param::<f64>())
        .map(|x: f64| format!("expt({} = {})", x, x.exp2()));
    let math_log = warp::get()
        .and(math_root)
        .and(warp::path("log"))
        .and(warp::path::param::<f64>())
        .map(|x: f64| format!("log({}) = {}", x, x.log2()));
    let math_help = warp::get()
        .and(math_root)
        .and(warp::path::end())
        .map(|| "The Math API:\n1. /math/sqrt/:f64\n2. /math/expt/:f64\n3. /math/log/:f64");
    let math = math_help.or(math_sqrt.or(math_expt).or(math_log));

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
    let class_query = warp::get()
        .and(class_root)
        .and(warp::path("get"))
        .and(warp::query::<HashMap<String, String>>())
        .map(|m: HashMap<String, String>| match m.get("no") {
            Some(k) => Response::builder().body(format!("{}: {}", k, "Apple")),
            None => Response::builder()
                .status(StatusCode::BAD_REQUEST)
                .body(String::from("No found.")),
        });
    let class_help = class_root
        .and(warp::get())
        .and(warp::path::end())
        .map(|| "The Class API:\n1. /class/verify/:u32\n2. /class/get?no=");
    let class = class_help.or(class_verify).or(class_query);

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
