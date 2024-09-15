// use std::mem::{self, ManuallyDrop, MaybeUninit};

// pub struct Umbra {
//     prefix: [u8; 4],
//     data: Data,
//     len: u32,
// }

// union Data {
//     buf: [u8; 8],
//     ptr: ManuallyDrop<[u8; 0]>,
// }

// impl Umbra {
//     pub fn new(s: &str) -> Self {
//         let bytes = s.as_bytes();
//         let len = s.len();
//         let mut prefix = [0u8; 4];
//         let buf = [0u8; 8];
//         let data = if len <= 12 {
//             let mut buf = [0u8; 8];
//             if len <= 4 {
//                 prefix.copy_from_slice(&bytes[..len]);
//             } else {
//                 prefix.copy_from_slice(&bytes[..4]);
//                 buf[..len - 4].copy_from_slice(&bytes[4..]);
//             }
//             Data { buf }
//         } else {
//             prefix.copy_from_slice(&bytes[..4]);
//             unsafe {
//                 Data {
//                     ptr: ManuallyDrop::new(&bytes[12..]),
//                 }
//             }
//         };
//         Self {
//             prefix,
//             data,
//             len: len as u32,
//         }
//     }
// }

// #[cfg(test)]
// mod tests {
//     use super::*;
//     use std::mem;

//     #[test]
//     fn size_of() {
//         assert_eq!(16, mem::size_of::<Umbra>());
//     }

//     #[test]
//     fn new() {
//         let _u1 = Umbra::new("abc");
//     }
// }
