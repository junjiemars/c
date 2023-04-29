use warp::Filter;

#[tokio::main]
async fn main() {
    let root = warp::path::end().map(|| "Welcome to RESTful!");
    let routes = root.with(warp::cors().allow_any_origin());

    warp::serve(routes).run(([127, 0, 0, 1], 9090)).await;
}
