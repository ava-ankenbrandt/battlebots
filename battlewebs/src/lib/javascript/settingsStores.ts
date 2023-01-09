import { PersistentStore } from "./persistentStore";

export const joystick_modes = ["buttons", "joystick"];
export const joystick_mode = new PersistentStore<string>("joystick_mode", joystick_modes[0]);

export const a_b_modes = ["toggle", "hold"];
export const a_b_mode = new PersistentStore<string>("a_b_mode", a_b_modes[0]);

export const servo_modes = ["toggle", "hold"];
export const servo_mode = new PersistentStore<string>("servo_mode", servo_modes[0]);

export const a_b_reverse_modes = ["none", "a reverses b", "x/y reverses a/b"];
export const a_b_reverse = new PersistentStore<string>("a_b_reverse", a_b_reverse_modes[0]);

export const reverse_A = new PersistentStore<boolean>("reverse_A", false);
export const reverse_B = new PersistentStore<boolean>("reverse_B", false);
export const reverse_L = new PersistentStore<boolean>("reverse_L", false);
export const reverse_R = new PersistentStore<boolean>("reverse_R", false);
export const switch_L_R_defs = new PersistentStore<boolean>("switch_L_R_defs", false);

export const reverse_S1 = new PersistentStore<boolean>("reverse_S1", false);
export const reverse_S2 = new PersistentStore<boolean>("reverse_S2", false);

