import { get_store_value } from "svelte/internal";
import { writable, type Readable, type Writable } from "svelte/store"

export class ButtonTracker implements Readable<boolean> {
    private buttonName: string

    private isDownStore: Writable<boolean>;
    public subscribe: Writable<boolean>["subscribe"];

    constructor (buttonName: string) {
        this.buttonName = buttonName
        this.isDownStore = writable(false);
        this.subscribe = this.isDownStore.subscribe;

    }
    mousedown (e: Event) {
        if (get_store_value(this.isDownStore) === false) {
            // console.log(`${this.buttonName} was clicked`)
            this.isDownStore.set(true);
        }
    }
    mouseup (e: Event) {
        if (get_store_value(this.isDownStore) === true) {
            // console.log(`${this.buttonName} was unclicked`)
            this.isDownStore.set(false)}
        }
}