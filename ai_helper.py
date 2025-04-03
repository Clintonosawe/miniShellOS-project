# ai_helper.py
import sys
from gpt4all import GPT4All

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 ai_helper.py \"Your question here\"")
        sys.exit(1)

    prompt = " ".join(sys.argv[1:])
    print("🤖 Running GPT4All locally...")

    try:
        # Specify the full relative path to the model file.
        # Since the file is located in "models/q4_0-orca-mini-3b.gguf" relative to the project root,
        # we set model_name to "models/q4_0-orca-mini-3b.gguf" and model_path to "."
        model = GPT4All("models/q4_0-orca-mini-3b.gguf", model_path=".", allow_download=False)
        
        with model.chat_session() as session:
            response = session.generate(prompt)
        
        print("\n🧠 AI Response:\n")
        print(response.strip())

    except Exception as e:
        print(f"❌ Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
