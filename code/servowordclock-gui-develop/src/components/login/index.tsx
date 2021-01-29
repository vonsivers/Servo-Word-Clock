import { h, Component } from "preact";
import * as style from "./style.css";
import Button from "preact-material-components/Button";
import TextField from "preact-material-components/TextField";
import "preact-material-components/TextField/style.css";
import "preact-material-components/Button/style.css";
import "preact-material-components/Theme/style.css";
import { route } from "preact-router";
import Constants from "../../Constants";
import { SWCClient } from "../../domain/SWCClient";

class Login extends Component<Props, State> {
    onClickLogin(): void {
        this.props.client.login(this.state.login).then(success => {
            if (success) {
                route(Constants.routes.Home);
            } else {
                this.setState({ loginFailed: true });
            }
        });
    }

    render() {
        return (
            <div class={style.login}>
                <h1>Login</h1>
                <p>
                    <label htmlFor="login">Password</label>
                    <TextField
                        id="login"
                        class={style.full}
                        value={this.state.login}
                        onChange={e =>
                            this.setState({
                                login: (e.target as HTMLInputElement).value
                            })
                        }
                    />
                </p>
                {this.state.loginFailed && (
                    <div class={style.loginFailed}>Login failed</div>
                )}
                <div class={style.textRight}>
                    <Button onClick={() => this.onClickLogin()}>Login</Button>
                </div>
            </div>
        );
    }
}

interface State {
    isLoading: boolean;
    login: string;
    loginFailed: boolean;
}
interface Props {
    client: SWCClient;
}

export default Login;
