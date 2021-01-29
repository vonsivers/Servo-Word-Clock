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
    return input
        .split(":")
        .map(i => i.padStart(2, "0"))
        .join(":");
}

export const baseApiUrl = process.env.PREACT_APP_API_BASE_PATH || "";

export default Constants;
