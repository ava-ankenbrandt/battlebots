/**
 * GCODE Spec
 * 
 * There are 4 types of signals being sent:
 * 1. Watchdog `W` - every x seconds. If wathdog is missed for some time, turn everything off
 * 2. PWM `P<channel_id> V<power, -255:255>` - PWM signal for a specific channel.
 *      L: 1, R: 2, A: 3, B: 4
 *      Positive is forward, negative is backwards.
 * 3. Servo Control `S<channel_id> A<0-180 degrees>` - Servo control value
 * 4. Note `N<tone, 01-15, 00 is no sound> - A single note. These are played live as they're received.
 *      if the watchdog times out, sound stops.
 */

import { writable, type Readable, type Writable } from "svelte/store";

export const message_types = {
  WATCHDOG: "W",
  PWM: "P",
  SERVO_CONTROL: "S",
  NOTE: "N"
} as const

export type MessageTypes = keyof typeof message_types

export abstract class Message {
  abstract to_string(): string;
  abstract get type(): MessageTypes
}

export class WatchdogMessage implements Message {
  get type(): MessageTypes {
    return "WATCHDOG"
  }
  to_string(): string {
      return "W"
  }
}

export class PwmMessage implements Message { // TODO: check setting and *-1 if it's set
  private power: string;
  private channel_id: string;

  constructor(channel_id: number, power: number)
  {
    if (power > 255) {power = 255;}
    if (power < -255) { power = -255;}
    if (!Number.isInteger(power)) {
      power = Math.round(power);
    }
    power = power + 255; // now always positive :)

    this.power = power.toString().padStart(3, '0');
    this.channel_id = channel_id.toString().padStart(2, '0');
  }

  to_string(): string {
    return `P${this.channel_id} V${this.power}`
  }

  get type(): MessageTypes {
    return "PWM"
  }
}

export class HornMessage implements Message {
  private note: string;
  private useless = '000';

  constructor(note: number) {
    this.note = note.toString().padStart(2, '0');
  }

  to_string(): string {
      return `N${this.note} U${this.useless}`;
  }

  get type(): MessageTypes {
    return "NOTE";
  }
}

export class WebsocketManager implements Readable<boolean> {
  private ws: WebSocket
  public subscribe: Writable<boolean>['subscribe'];
  private isConnectedStore: Writable<boolean>; // whether the connection is open

  constructor(private readonly connection_string: string) {
    this.isConnectedStore = writable(false);
    this.subscribe = this.isConnectedStore.subscribe;
    console.log(1, this.isConnectedStore);

    this.connect()
  }

  private connect() {
    this.ws = new WebSocket(this.connection_string)

    this.ws.addEventListener('open', this.on_open.bind(this));
    this.ws.addEventListener('close', this.on_close.bind(this));
    this.ws.addEventListener('message', this.on_message.bind(this));
    this.ws.addEventListener('error', this.on_error.bind(this));
  }

  public send_command(command: Message) {
    console.debug("sending ws message... " + command.to_string());
    try {
    this.ws.send(command.to_string())
    } catch (error) { console.error("failed to send ws message"); }
  }

  private on_open(e: WebSocketEventMap["open"]) {
    console.log("Websocket opened", e)
    this.isConnectedStore.set(true);
  }

  private on_close(e: WebSocketEventMap["close"]) {
    console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);
    this.isConnectedStore.set(false);
    setTimeout(() => {
      this.connect()
    }, 30000);
  }

  private on_message(e: WebSocketEventMap["message"]) {
    console.log('Websocket message:', e.data);
  }

  private on_error(e: WebSocketEventMap["error"]) {
    console.error('Websocket error:', e)
    this.isConnectedStore.set(false);
    // setTimeout(() => {
    //   this.connect()
    // }, 10000);
  }
}

export const websocket_manager = new WebsocketManager(`ws://${window.location.hostname}/ws`); // running on the laptop
// export const websocket_manager = new WebsocketManager(`ws://10.10.1.1/ws`); // running on the phone/esp32 combo