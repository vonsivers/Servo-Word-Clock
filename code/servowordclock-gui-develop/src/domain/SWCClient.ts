import { resolveConfig } from "prettier";
import { apiGetParsed, apiPostFormData, apiPostLogin, Auth } from "./apiUtils";

export class SWCClient {
    auth: Auth;
    keepAliveTimeoutHandle: number | undefined;
    constructor(onAccessDenied: () => void) {
        this.auth = {
            key: "",
            onAccessDenied: () => {
                this.removeKeepAlive();
                onAccessDenied();
            },
            onSuccess: () => {
                this.assureKeepAlive();
            }
        };
    }

    private removeKeepAlive() {
        if (this.keepAliveTimeoutHandle) {
            window.clearTimeout(this.keepAliveTimeoutHandle);
        }
    }
    private assureKeepAlive() {
        if (!this.keepAliveTimeoutHandle) {
            this.keepAlive();
        }
    }

    private keepAlive() {
        this.keepAliveTimeoutHandle = window.setTimeout(
            this.keepAlive.bind(this),
            5 * 60 * 1000
        );
        apiGetParsed<KeepAlive>("login", this.auth).then(auth => {
            if (auth && Object.keys(auth).length) {
                this.auth.key = Object.keys(auth)[0];
            }
        });
    }

    public login(login: string): Promise<boolean> {
        return apiPostLogin("login", login).then(result => {
            if (result) {
                this.auth.key = result;
                return true;
            } else {
                this.auth.key = undefined;
                return false;
            }
        });
    }

    public setPassword(payload: ChangePassword): Promise<{}> {
        return apiPostFormData("changepwd", payload, this.auth);
    }

    public getTimeSettings(): Promise<TimeSettings> {
        return apiGetParsed("timesettings", this.auth);
    }

    public setTimeSettings(payload: TimeSettings): Promise<{}> {
        return apiPostFormData("timesettings", payload, this.auth);
    }

    public getDisplayEffects(): Promise<DisplayEffects> {
        return apiGetParsed("displayeffects", this.auth);
    }

    public setDisplayEffects(payload: DisplayEffects): Promise<{}> {
        return apiPostFormData("displayeffects", payload, this.auth);
    }

    public getNightMode(): Promise<NightMode> {
        return apiGetParsed("nightmode", this.auth);
    }

    public setNightMode(payload: NightMode): Promise<{}> {
        return apiPostFormData("nightmode", payload, this.auth);
    }

    public getDisplayEffectsSettings(): Promise<DisplayEffectsSettings> {
        return apiGetParsed("displayeffects/settings", this.auth);
    }

    public getNightModeSettings(): Promise<NightModeSettings> {
        return apiGetParsed("nightmode/settings", this.auth);
    }

    public getTimeSettingsSettings(): Promise<TimeSettingsSettings> {
        return apiGetParsed("timesettings/settings", this.auth);
    }

    public getWifi(): Promise<Wifi> {
        return apiGetParsed("wifi", this.auth);
    }

    public setWifi(payload: Wifi): Promise<{}> {
        return apiPostFormData("wifi", payload, this.auth);
    }

    public getWifiSettings(): Promise<WifiSettings> {
        return apiGetParsed("wifisettings", this.auth);
    }
}
export interface Login {
    login: string;
}
export interface ChangePassword {
    newlogin: string;
}
export interface TimeSettings {
    mode: TimeSettingsMode; // (0 = timezone, 1 = manual)
    timezone: string; // = (0-x) [wenn mode = 0]
    manual_time: string; // = (time)
    manual_date: string; // = (yyyy-mm-dd)
}
export type TimeSettingsMode = "internet" | "custom";
export interface DisplayEffects {
    brightness: string; // = (0 - 100)
    effect_hour: string; // = (effect_type )
    effect_5minute: string; // = (effect_type )
    color_mode_dot: string; // = (color_mode_dot_type )
    color_dot: string; // = #xxxxxx [wenn color_mode_dot = 0]
    color_mode_word: string; // =(color_mode_word_type)
    color_word: string; // = #xxxxxx [wenn color_mode_word = 0]
    color_mode_background: string; // = (color_mode_background_type)
    color_background: string; // = #xxxxxx [wenn color_mode_background = 0]
}
export interface DisplayEffectsSettings {
    effect_type: string[]; // = (string, string, ....)
    color_mode_dot_type: string[]; // = (string, string, ....)
    color_mode_word_type: string[]; // = (string, string, ....)
    color_mode_background_type: string[]; // = (string, string, ....)
}
export interface Wifi {
    ssid: string;
    password: string;
    state: string;
}
export interface NightMode {
    mode: string; // (disabled, mode_type...)
    weekday_start: string; //:string, // (time) [wenn mode != 0]
    weekday_end: string; // (time) [wenn mode != 0]
    weekend_start: string; // (time) [wenn mode != 0]
    weekend_end: string; // (time) [wenn mode != 0]
}
export interface NightModeSettings {
    mode_type: string[]; // = (string, string, ....) ohne disabled
}
export interface TimeSettingsSettings {
    zone_type: string[]; // = (string, string, ....)
}
export interface WifiSettings {
    [ssid: string]: string[]; // signal-strength, secure
}
interface KeepAlive {
    [auth: string]: []; //empty
}
