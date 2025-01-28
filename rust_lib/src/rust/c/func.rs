use std::ffi;

#[no_mangle]
pub extern "C" fn hello_str() -> *const ffi::c_char {
    let s = ffi::CString::new("Hello Rust FFI").unwrap();
    s.into_raw()
}

#[no_mangle]
pub extern "C" fn free_str(ptr: *const ffi::c_char) {
    unsafe {
        let _ = ffi::CString::from_raw(ptr as *mut _);
    };
}