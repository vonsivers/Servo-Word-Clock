import { baseApiUrl } from "../Constants";

export interface Auth{
    onNoAuth: () => void;
    login: string;
}

export function apiPostFormData<TResult>(
    route: string,
    input: object,
	auth: Auth
): Promise<{}> {
    const body = new FormData();
    for (const key in input) {
        body.append(key, input[key]?.toString() ?? null);
    }
	body.append("login", auth.login);
    return new Promise((resolve, reject) => {
		fetch(`${baseApiUrl}${route}`, {
			method: "post",
			body,
			credentials: "include"
		}).then(response => {
			if(response.status == 403) {
				auth.onNoAuth()
			}else{
				resolve(response);
			}
		})
            .catch(reject);	
	});
}

export function apiGetParsed<TResult>(
	route: string,
	auth: Auth
): Promise<TResult> {
    return new Promise((resolve, reject) => {
        fetch(`${baseApiUrl}${route}?login=${auth.login}`, {
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
				} else if(response.status == 403) {
					auth.onNoAuth()
                } else {
                    reject(response);
                }
            })
            .catch(reject);
    });
}
