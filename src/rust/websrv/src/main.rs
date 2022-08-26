#![allow(unused)]

use std::{
    fs,
    io::{prelude::*, BufReader},
    net::{TcpListener, TcpStream},
};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();

    for stream in listener.incoming() {
        let stream = stream.unwrap();
        on_connect(stream);
    }
}

fn on_connect(mut ss: TcpStream) {
    let br = BufReader::new(&mut ss);
    let req_line = br.lines().next().unwrap().unwrap();

    if req_line == "GET / HTTP/1.1" {
        let stauts_line = "HTTP/1.1 200 OK";
        let contents = fs::read_to_string("out/bin/h.html").unwrap();
        let length = contents.len();
        let res = format!("{stauts_line}\r\nContent-Length: {length}\r\n\r\n{contents}");
        ss.write_all(res.as_bytes()).unwrap();
    } else {
        ss.write_all("HTTP/1.1 200 OK\r\n\r\n".as_bytes()).unwrap();
    }
}
