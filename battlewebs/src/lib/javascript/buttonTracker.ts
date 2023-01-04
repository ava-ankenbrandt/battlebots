export class ButtonTracker {
    private buttonName: string
    public isDown: boolean = false

    constructor (buttonName: string) {
        this.buttonName = buttonName
    }
    mousedown (e: Event) {
        if (!this.isDown)
        {console.log(`${this.buttonName} was clicked`)
        this.isDown = true}
    }
    mouseup (e: Event) {
        if (this.isDown)
        {console.log(`${this.buttonName} was unclicked`)
        this.isDown = false}
    }
}