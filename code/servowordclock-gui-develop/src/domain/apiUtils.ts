import { baseApiUrl } from "../Constants";

export interface Auth {
    onAccessDenied: () => void;
    onSuccess: () => void;
    key: string;
}

export function apiPostFormData(
    route: string,
    input: object,
    auth: Auth
): Promise<Response> {
    const body = new FormData();
    for (const key in input) {
        body.append(key, input[key]?.toString() ?? null);
    }
    body.append("key", auth.key);
    return new Promise((resolve, reject) => {
        fetch(`${baseApiUrl}${route}`, {
            method: "post",
            body,
            credentials: "include"
        })
            .then(response => {
                if (response.status == 403) {
                    auth.onAccessDenied();
                } else {
                    auth.onSuccess();
                    resolve(response);
                }
            })
            .catch(reject);
    });
}

export function apiPostLogin(
    route: string,
    login: string
): Promise<string | undefined> {
    const body = new FormData();
    body.append("login", login);
    return new Promise((resolve, reject) => {
        fetch(`${baseApiUrl}${route}`, {
            method: "post",
            body,
            credentials: "include"
        })
            .then(response => {
                if (response.status == 403) {
                    resolve(undefined);
                } else {
                    resolve(response.text());
                }
            })
            .catch(res => {
                console.warn("error on login", res);
                resolve(undefined);
            });
    });
}

export function apiGetParsed<TResult>(
    route: string,
    auth: Auth
): Promise<TResult> {
    return new Promise((resolve, reject) => {
        fetch(`${baseApiUrl}${route}?key=${auth.key}`, {
            headers: { "Content-Type": "text/plain" },
            method: "get",
            credentials: "include"
        })
            .then(response => {
                if (response.ok) {
                    response
                        .text()
                        .then(text => {
                            const result = text
                                .split("\n\n")
                                .map(p => p.split("\n"))
                                .reduce((obj, kv) => {
                                    obj[kv[0]] =
                                        kv.length === 2 ? kv[1] : kv.slice(1);
                                    return obj;
                                }, {} as TResult);
                            resolve(result);
                        })
                        .catch(reject);
                } else if (response.status == 403) {
                    auth.onAccessDenied();
                } else {
                    auth.onSuccess();
                    reject(response);
                }
            })
            .catch(reject);
    });
}
