# ai_helper.py
import sys
from transformers import AutoTokenizer, AutoModelForSeq2SeqLM

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 ai_helper.py \"Your question here\"")
        sys.exit(1)

    question = " ".join(sys.argv[1:])
    print("🧠 Loading FLAN-T5 model...")

    try:
        # Load tokenizer and model
        tokenizer = AutoTokenizer.from_pretrained("google/flan-t5-small")
        model = AutoModelForSeq2SeqLM.from_pretrained("google/flan-t5-small")

        # Prepare the prompt
        prompt = f"Answer the following question: {question}"
        input_ids = tokenizer(prompt, return_tensors="pt").input_ids

        # Generate a response
        output_ids = model.generate(input_ids, max_new_tokens=128)
        response = tokenizer.decode(output_ids[0], skip_special_tokens=True)

        print("\n🤖 AI Response:\n")
        print(response)

    except Exception as e:
        print(f"❌ Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
