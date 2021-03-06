class Drawing {
    private canvas: HTMLCanvasElement;
    private context: CanvasRenderingContext2D;  

    constructor() {
        let canvas = document.getElementById('MainCanvas') as HTMLCanvasElement;
        let context = canvas.getContext("2d");
        if(context !== null) {
            context.lineCap = 'round';
            context.lineJoin = 'round';
            context.strokeStyle = 'black';
            context.lineWidth = 1;

            this.canvas = canvas;
            this.context = context;
        } else {
            throw "Error: could not get the current 2d context for the canvas.";
        }
    }
    public clearCanvas() {
        this.context
            .clearRect(0, 0, this.canvas.width, this.canvas.height);
    }
    /**
     * circle
     * Draws a circle with the given radius
     * at the position given by (posx, posy)
     */
    public circle(posx: number, posy: number, radius: number):void {
        this.context.beginPath();
        this.context.arc(posx, posy, radius, 0, 2*Math.PI);
        this.context.stroke();
    }
}

export {Drawing}