const Constants = {
    routes: {
        Home: "/home",
        Wifi: "/wifi/",
        TimeSettings: "/time-settings/",
        Display: "/display/",
        NightMode: "/night-mode/",
        ChangePassword: "/change-password",
        Login: "/"
    }
};

export function sanitizeTime(input: string): string {
    const time = input.split(":");
    return (time[0] || "").padStart(2, "0") + ":" + (time[1] || "").padStart(2, "0")
}

export function sanitizeDate(input: string): string {
    const date = input.split("-");
    return (date[0] || "") + "-" + (date[1] || "").padStart(2, "0") + "-" + (date[2] || "").padStart(2, "0")
}

export const baseApiUrl = process.env.PREACT_APP_API_BASE_PATH || "";

export default Constants;
