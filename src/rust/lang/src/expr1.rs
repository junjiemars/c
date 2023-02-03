/*
 * https://doc.rust-lang.org/stable/reference/expressions.html
 */

pub(crate) fn test() {
    op_question_mark();
}

fn op_question_mark() {
    // ? cannot be overloaded

    fn try_parse(s1: &str, s2: &str) -> Result<i32, std::num::ParseIntError> {
        let a: i32 = s1.parse()?;
        let b: i32 = s2.parse()?;
        Ok(a + b)
    }

    let res = try_parse("123", "45a");
    assert!(res.is_err());

    fn try_option_some() -> Option<u8> {
        let val = Some(1)?;
        Some(val)
    }
    fn try_option_none() -> Option<u8> {
        let val = None?;
        Some(val)
    }

    assert_eq!(try_option_some(), Some(1));
    assert_eq!(try_option_none(), None);
}
