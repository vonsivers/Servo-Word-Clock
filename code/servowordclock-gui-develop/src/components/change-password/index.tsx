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

class ChangePassword extends Component<Props, State> {
    onClickChangePassword(): void {
        if (this.state.password && this.state.password === this.state.confirm) {
            this.props.client
                .setPassword({ newlogin: this.state.password })
                .then(() => {
                    route(Constants.routes.Home);
                });
        }
    }

    render() {
        return (
            <div class={style.changePassword}>
                <h1>Change Password</h1>
                <div>
                    <label htmlFor="password">New password</label>
                    <TextField
                        id="password"
                        label="Password"
                        helperText="Your password"
                        class={style.full}
                        value={this.state.password}
                        onChange={e =>
                            this.setState({
                                password: (e.target as HTMLInputElement).value
                            })
                        }
                    />
                </div>
                <div>
                    <label htmlFor="confirm">Confirm password</label>
                    <TextField
                        id="confirm"
                        label="Confirm password"
                        helperText="Confirm your password"
                        class={style.full}
                        value={this.state.confirm}
                        onChange={e =>
                            this.setState({
                                confirm: (e.target as HTMLInputElement).value
                            })
                        }
                    />
                </div>
                {this.state.password &&
                    this.state.password !== this.state.confirm && (
                        <div class={style.error}>
                            Passwords don&apos;t match
                        </div>
                    )}
                <div class={style.textRight}>
                    <Button
                        onClick={() => this.onClickChangePassword()}
                        disabled={
                            !this.state.password ||
                            this.state.password !== this.state.confirm
                        }
                    >
                        Change password
                    </Button>
                </div>
            </div>
        );
    }
}

interface State {
    isLoading: boolean;
    password: string;
    confirm: string;
    loginFailed: boolean;
}
interface Props {
    client: SWCClient;
}

export default ChangePassword;
