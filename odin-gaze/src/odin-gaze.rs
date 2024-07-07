extern crate chrono;
extern crate chrono_tz;
extern crate geocoding;
extern crate open_meteo_rs;

use geocoding::{Forward, Openstreetmap};
use open_meteo_rs::forecast::{
    CellSelection, Elevation, Options, TemperatureUnit,
};
use open_meteo_rs::Client;
use std::ffi::{CStr, CString};
use std::os::raw::c_char;

fn get_coordinates(
    location_name: &str,
) -> Result<(f64, f64), Box<dyn std::error::Error>> {
    let osm = Openstreetmap::new();
    let locations = osm.forward(&location_name)?;

    if let Some(location) = locations.first() {
        Ok((location.y(), location.x()))
    } else {
        Err("Location not found".into())
    }
}

async fn get_weather_lat_lng_async(
    lat: f64,
    lng: f64,
) -> Result<String, Box<dyn std::error::Error>> {
    let client = Client::new();
    let mut opts = Options::default();

    opts.location = open_meteo_rs::Location { lat, lng };
    opts.elevation = Some(Elevation::Nan);
    opts.temperature_unit = Some(TemperatureUnit::Celsius);
    opts.cell_selection = Some(CellSelection::Land);

    let start_date = chrono::offset::Utc::now().date_naive();
    opts.start_date = Some(start_date);
    opts.end_date = Some(start_date);
    opts.current.push("temperature_2m".into());

    match client.forecast(opts).await {
        Ok(forecast) => {
            if let Some(current) = forecast.current {
                if let Some(temp_value) = current.values.get("temperature_2m") {
                    Ok(format!("{}", temp_value.value))
                } else {
                    eprintln!("Temperature data is not available");
                    Err("Temperature data is not available".into())
                }
            } else {
                eprintln!("No current data available");
                Err("No current data available".into())
            }
        }
        Err(e) => {
            eprintln!("Cannot get information about weather: {}", e);
            Err(e.into())
        }
    }
}

#[no_mangle]
pub extern "C" fn getWeatherName(
    location_name: *const c_char,
) -> *mut c_char {
    let c_str = unsafe { CStr::from_ptr(location_name) };
    let location = match c_str.to_str() {
        Ok(s) => s,
        Err(_) => return std::ptr::null_mut(),
    };

    match get_coordinates(location) {
        Ok((lat, lng)) => {
            let rt = tokio::runtime::Runtime::new().unwrap();
            match rt.block_on(get_weather_lat_lng_async(lat, lng)) {
                Ok(result) => CString::new(result).unwrap().into_raw(),
                Err(_) => std::ptr::null_mut(),
            }
        }
        Err(_) => std::ptr::null_mut(),
    }
}

#[no_mangle]
pub extern "C" fn getWeatherLatLng(lat: f64, lng: f64) -> *mut c_char {
    let rt = tokio::runtime::Runtime::new().unwrap();
    match rt.block_on(get_weather_lat_lng_async(lat, lng)) {
        Ok(result) => CString::new(result).unwrap().into_raw(),
        Err(_) => std::ptr::null_mut(),
    }
}

#[no_mangle]
pub extern "C" fn freeCStyleString(s: *mut c_char) {
    if s.is_null() {
        return;
    }
    unsafe {
        let _let_ = CString::from_raw(s);
    }
}
